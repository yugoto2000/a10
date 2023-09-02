/*****************************************************
@file     after_calib_analysis.C
@brief
@author   Yu Goto
@date     2023.06.05
@note     first edit:2023.06.05
****************************************************/
#include <TFile.h>
#include <TH1.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "TString.h"
#include <stdio.h>  //printf
#include <stdlib.h> //stod??
#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCut.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TEventList.h"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorD.h"
#include "TStopwatch.h"
#include <cmath>
#include <sstream> //csv読みたいとき


TH1D *take(TString filename, TString histname)
{
  TH1D *h;
  TFile *file = new TFile(Form("%s", filename.Data())); 
  h = (TH1D *)file->Get(Form("%s", histname.Data()));  
  return h;
  h->Clear();
  file->Close();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<double> a = {};
std::vector<double> b = {};
std::vector<double> c = {};
std::vector<double> d = {};

//4列のcsvを読む
void set_vector(TString filename, std::vector<double> *a, std::vector<double> *b, std::vector<double> *c, std::vector<double> *d)
{
  std::vector<double> a_tmp = {};
  std::vector<double> b_tmp = {};
  std::vector<double> c_tmp = {};
  std::vector<double> d_tmp = {};

  Int_t n = 0;
  Double_t tmpdouble = 0;
  string str = "";
  int j = 0;
  ifstream ifs(Form("%s", filename.Data()));
  if (ifs)
    cout << "file_exist" << endl;
  while (getline(ifs, str)) // ファイルの中身を一行ずつ読み取る
  {
    std::string tmp = "";
    istringstream stream(str); // 区切り文字がなくなるまで文字を区切っていく

    for (j = 0; j < 4; j++)
    {
      getline(stream, tmp, ' ');
      double tmpdouble = stod(tmp);
      if (j == 0)
      {
        a_tmp.push_back(tmpdouble);
      }
      if (j == 1)
      {
        b_tmp.push_back(tmpdouble);
      }
      if (j == 2)
      {
        c_tmp.push_back(tmpdouble);
      }
      if (j == 3)
      {
        d_tmp.push_back(tmpdouble);
      }
    }
    n++;
    j = 0;

    *a = a_tmp;
    *b = b_tmp;
    *c = c_tmp;
    *d = d_tmp;

  }

  ifs.close();
}





void check_csv()
{
  set_vector("fit.csv", &a, &b, &c, &d);
  cout << a[0] << a[1] << endl;
  cout << b[0] << b[1] << endl;
  cout << c[0] << c[1] <<  endl;
  cout << d[0] << d[1] <<  endl;
}





//main関数
void tof(TString csvname = "fit.csv",TString upfilename = "minus_compton_histgram/up/All_Run_Sum.root",TString downfilename = "minus_compton_histgram/down/All_Run_Sum.root",TString uphistname = "hTOF_all",TString downhistname = "hTOF_all")
{



  std::ofstream csv_file0(Form("%s", csvname.Data()));  
  TH1D *hist_TOF_up;
  TH1D *hist_TOF_down;
  hist_TOF_up = take(Form("%s",upfilename.Data()),Form("%s",uphistname.Data()));
  hist_TOF_down = take(Form("%s",downfilename.Data()),Form("%s",downhistname.Data()));
  TH1D *hist_TOF_BG_up = new TH1D("h_both_0", ";PulseHeight;Counts", 1400, 1100, 2500);
  TH1D *hist_TOF_BG_down = new TH1D("h_both_0", ";PulseHeight;Counts", 1400, 1100, 2500);
  double integral_up1_error;
  double integral_down1_error;
  double integral_up1 = hist_TOF_up->IntegralAndError(1749, 1825,integral_up1_error); 
  double integral_down1 = hist_TOF_down->IntegralAndError(1749, 1825,integral_down1_error);

  for (int i = 1100; i < 2500; i++)
  {
    if ((i < 1600) || (i > 1950))
    {
      cout<<hist_TOF_up->GetBin(i)<<" "<<hist_TOF_up->GetBinContent(hist_TOF_up->GetBin(i))<<endl;
      cout<<endl;
      hist_TOF_BG_up->SetBinContent(hist_TOF_up->GetBin(i)-1100, hist_TOF_up->GetBinContent(hist_TOF_up->GetBin(i)));
      hist_TOF_BG_up->SetBinError(hist_TOF_up->GetBin(i)-1100, hist_TOF_up->GetBinError(hist_TOF_up->GetBin(i)));
      hist_TOF_BG_down->SetBinContent(hist_TOF_down->GetBin(i)-1100, hist_TOF_down->GetBinContent(hist_TOF_down->GetBin(i)));
      hist_TOF_BG_down->SetBinError(hist_TOF_down->GetBin(i)-1100, hist_TOF_down->GetBinError(hist_TOF_down->GetBin(i)));
    }
  }


  TF1 *f_3 = new TF1("f_3", "[3]*x^3+[2]*x^2+[1]*x+[0]", 1400, 2100);
  hist_TOF_BG_up->Fit("f_3", "", "", 1400, 2100);
  hist_TOF_BG_down->Fit("f_3", "", "", 1400, 2100);
  csv_file0 << f_3->GetParameter(3) << " " << f_3->GetParameter(2) << " " << f_3->GetParameter(1) << " " << f_3->GetParameter(0) << endl;
  csv_file0 << f_3->GetParameter(3) << " " << f_3->GetParameter(2) << " " << f_3->GetParameter(1) << " " << f_3->GetParameter(0) << endl;
  set_vector(Form("%s", csvname.Data()), &a, &b, &c, &d);
  TF1 *f0 = new TF1("f0", Form("%.18f*x^3+%.18f*x^2+%.18f*x + %.18f", a[0], b[0], c[0], d[0]), 1400, 2100);
  TF1 *f1 = new TF1("f1", Form("%.18f*x^3+%.18f*x^2+%.18f*x + %.18f", a[1], b[1], c[1], d[1]), 1400, 2100);
  


  for (int i = 1100; i < 2500; i++)
  {
    hist_TOF_up->SetBinContent(i, hist_TOF_up->GetBinContent(i) - (a[0] * i * i * i + b[0] * i * i + c[0] * i + d[0]));
    hist_TOF_down->SetBinContent(i, hist_TOF_down->GetBinContent(i) - (a[1] * i * i * i + b[1] * i * i + c[1] * i + d[1]));
  }
 

  double integral_up2_error=1;//1Gammaの範囲。2Gammaの時は(1714,1867)
  double integral_down2_error=1;
  double integral_up2 = hist_TOF_up->IntegralAndError(1749, 1825,integral_up2_error);//1Gammaの範囲。2Gammaの時は(1714,1867)
  double integral_down2 = hist_TOF_down->IntegralAndError(1749, 1825,integral_down2_error);
   
  
  // cout << endl;
  // cout << a[0] << a[1] << endl;
  // cout << b[0] << b[1] << endl;
  // cout << c[0] << c[1] <<  endl;
  // cout << d[0] << d[1] <<  endl;
  // cout << "integral_up_subBG   =" << integral_up2 <<" ± "<<integral_up2_error<< endl;
  // cout << "integral_down_subBG =" << integral_down2 <<" ± "<<integral_down2_error<< endl;
  // cout << endl;
  
  double asymmetry_subBG = (integral_up2 - integral_down2) / (integral_up2 + integral_down2); //
  double asymmetry_before_subBG = (integral_up1 - integral_down1) / (integral_up1 + integral_down1); //
  double error1 = 2 * sqrt((integral_down1 * integral_down1 * integral_up1_error) + (integral_up1 * integral_up1 * integral_down1_error) ) / (integral_down1 * integral_down1 + integral_up1 * integral_up1);
  double error2 = 2 * sqrt((integral_down2 * integral_down2 * integral_up2_error) + (integral_up2 * integral_up2 * integral_down2_error) ) / (integral_down2 * integral_down2 + integral_up2 * integral_up2);
  
  cout << "asymmetry_before_subBG = "<<asymmetry_before_subBG << " ± "<< error1 << endl;
  cout << "asymmetry_subBG        = "<<asymmetry_subBG << " ± "<< error2 << endl;
 
  hist_TOF_up->SetLineColor(kRed);
  hist_TOF_down->SetLineColor(kBlue);
  hist_TOF_up->GetXaxis()->SetRangeUser(1400, 2200);
  hist_TOF_down->GetXaxis()->SetRangeUser(1400, 2200);
  hist_TOF_up->Draw("same");
  hist_TOF_down->Draw("same");
  f0->Draw("same");
  f1->Draw("same");


}