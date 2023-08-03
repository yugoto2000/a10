void Draw_csv()
{
  double a[3] ={};
  Int_t n=0;
  Double_t tmpdouble = 0;
  string str = "";
  int j = 0;  
  
  TH1F *HIST = new TH1F("h", "h", 600, 400, 1000);
  ifstream ifs("He_pol.csv"); 
  
  while(getline(ifs, str))  // ファイルの中身を一行ずつ読み取る
  {
    std::string tmp = "";
    istringstream stream(str);// 区切り文字がなくなるまで文字を区切っていく
   
    while (getline(stream, tmp, ' ') )
    {
      double tmpdouble = stod(tmp);
      a[j] = tmpdouble;
      j++;
      }
    
    HIST->SetBinContent(HIST->FindBin(a[0]), a[1]);//Fillでもいいはずだけどうまくいかなかったので
    HIST->SetBinError(HIST->FindBin(a[0]), a[2]);
    
    ///////////////////////////////////////確認用///////////////////////////////////////
   // cout << a[0] <<" "<<a[1]<<" "<< a[2]<< endl;
   // cout << a[0] <<" "<<HIST->GetBinContent(HIST->FindBin(a[0]))<<" "<< HIST->GetBinError(HIST->FindBin(a[0]))<< endl;
    ///////////////////////////////////////確認用///////////////////////////////////////
    
    n++;  // 次の配列に移る
    j = 0;
  }
  
  TCanvas *c2 = new TCanvas("c2", "c2");
  HIST->Draw("same");
  c2->Show();
  
  ifs.close();
}