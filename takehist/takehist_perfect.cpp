TH1D *take1_dir(TString filename, TString dirname, TString histname)
{
    int runnum = 0;
    TH1D *h;
    TFile *file = new TFile(Form("%s", filename.Data()));
    if (dirname = "")
    {
        h = (TH1D *)file->Get(Form("%s", histname.Data()));
    }
    else
    {
        TDirectory *dir = file->GetDirectory(Form("%s", dirname.Data()));
        h = (TH1D *)dir->Get(Form("%s", histname.Data()));
    }
    cout << "now inporting" << '"' << Form("%s", filename.Data()) << ":" << Form("%s", dirname.Data()) << ":" << Form("%s", histname.Data()) << '"' << "\r";
    if (h == nullptr)
    {
        cerr << "nannmo_naiyo!"
             << "\r" << endl;
    }
    return h;
}