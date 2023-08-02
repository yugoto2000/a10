TH1D* take_hist(TString option,int gate_option,int runnumber){//"up""down"option構造
  int runnum = 0;
  TH1D *h;
  TFile *file=new TFile(Form("outroot/%s/hist_run_0%d_000.root",option.Data(),runnumber));//ここでrootファイルを決める//option.Data()っていうのはoptionをchar*に変えて
  TDirectory *dir = file->GetDirectory(Form("hTOF_Li%d_gate",gate_option));//ROOTファイル中にディレクトリがなければここはコメントアウト
  h=(TH1D*)dir->Get(Form("hTOF_Li%d_gate_d%d",gate_option,gate_option+6));//ここはfileからgetでおけだと思う
  return h;
}
