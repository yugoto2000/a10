
void Draw_line(TString filename = "a.csv", int linestyle = 1)
{
    std::ifstream infile(Form("%s", filename.Data()));
    double x[12];
    int i = 0;
    TLine *line[12];
    while (i < 12)
    { // while (infile >> x[i]) はダメだった
        
        infile >> x[i];
        cout << x[i] * 1 << endl;
        line[i] = new TLine(x[i], 0, x[i], 1); // ヒストグラムのx=x[i]上に
        line[i]->SetLineStyle(linestyle);
        line[i]->Draw("same");
        i++;
    }
}

///a.csvの中に描きたい線のxを縦一列に羅列しておくとこれを回した時に線を上書きしてくれる
