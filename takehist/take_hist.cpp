
TH1D* takehist(TString option,int gate_option,int runnumber){//"up""down"option構造に
  int runnum = 0;
  TH1D *h;
  TFile *file=new TFile(Form("outroot/%s/hist_run_0%d_000.root",option.Data(),runnumber));//ここでrootファイルを決める//option.Data()っていうのはoptionをchar*に変えて
  TDirectory *dir = file->GetDirectory(Form("hTOF_Li%d_gate",gate_option));//ROOTファイル中にディレクトリがなければここはコメントアウト
  h=(TH1D*)dir->Get(Form("hTOF_Li%d_gate_d%d",gate_option,gate_option+6));//ここはfileからgetでいいと思う
    
  cout << "now inporting" << '"' << Form("%s", filename.Data()) << ":" << Form("%s", dirname.Data()) << ":" << Form("%s", histname.Data()) << '"' << "\r";
  if (h == nullptr)
  {
      cerr << "nannmo_naiyo!"
        << "\r" << endl;
  }
  return h;
}

///参照方法
///void Draw_hist(){
///TH1D *h0;
///h0= takeLi("up",477);////
///h0->Draw();
///}/////
