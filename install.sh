rm -r external

git clone https://github.com/Tessil/robin-map.git
git clone https://github.com/nlohmann/json.git
git clone https://github.com/dtschump/CImg.git

mkdir external/
mkdir docs/

mv robin-map/ external/
mv CImg/ external/
mv json/ external/