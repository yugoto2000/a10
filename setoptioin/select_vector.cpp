std::vector<int> my_vector = {};

std::vector<int> my_up = {477,480,842,845};//例
std::vector<int> my_down = {478,479,843,844};
std::vector<int> my_depol = {636,636,907,907};



void select_vector(std::vector<int> *my_vec,TString option){
  if (option =="up") {*my_vec = my_up;}
  else if (option =="down") {*my_vec = my_down;}
  else if (option =="depol") {*my_vec = my_depol;}
}

//////////////////////参照する方法//////////////////////////
//void reset_vector(TString option){
// select_vector(&my_vector,option.Data());///myベクターのアドレスを書き換える
//ここでmyvectorを使って作業すればいい
//}
