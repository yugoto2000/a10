std::vector<double> a = {}; // 例
std::vector<double> b = {};
std::vector<double> c = {};
std::vector<double> d = {};

void read_csv_and_set_vector(TString filename, std::vector<double> *a, std::vector<double> *b, std::vector<double> *c, std::vector<double> *d)
{
  std::vector<double> a_tmp = {}; // 例
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
      getline(stream, tmp, ',');

      double tmpdouble = stod(tmp);
      cout << tmpdouble << endl;
      if (j == 0)
        a_tmp.push_back(tmpdouble);
      if (j == 1)
        b_tmp.push_back(tmpdouble);
      if (j == 2)
        c_tmp.push_back(tmpdouble);
      if (j == 3)
        d_tmp.push_back(tmpdouble);
      // cout<<a_tmp[0]<<a_tmp[1]<<a_tmp[2]<<a_tmp[3]<<endl;
      j++;
    }
    n++; // 次の配列に移る
    j = 0;
    *a = a_tmp;
    *b = b_tmp;
    *c = c_tmp;
    *d = d_tmp;
  }

  ifs.close();
}

void aaaa()
{
    read_csv_and_set_vector("fit.csv", &a, &b, &c, &d);
    cout << a[0] << a[1] << a[2] << a[3] << endl;
    cout << b[0] << b[1] << b[2] << b[3] << endl;
    cout << c[0] << c[1] << c[2] << c[3] << endl;
    cout << d[0] << d[1] << d[2] << d[3] << endl;
}
