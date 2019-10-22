cp ../../Ceres_looping/outfiles/4l1F/*.root .
mv signal_selected.root signal_wzz+zzz.root
hadd signal_selected.root signal_wzz+zzz.root signal_h_selected.root
source rooutil/thisrooutil.sh 
source rooutil/root.sh
