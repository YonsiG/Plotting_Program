g++ -g -std=c++17 plots.C -I$ROOTSYS/include `root-config --libs ` -lMinuit -lGenVector -o plots.exe
