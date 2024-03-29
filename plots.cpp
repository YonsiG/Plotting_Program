//Time:2017.10.11
//Last Modified:2019.9.19
void plots()
{
/*******Switches********/
  bool Compare=true; //if you want to draw two plots, please set it true
  bool Stack=false;
  bool DoRatio=false; //if you want to draw the ratio beneath the plots, please set it true (Set Compare mode true first)
  bool SetXRange=false;
  bool SetYRange=false;
  bool Normalize=false; //Set Compare mode first, normalize to plot1
  bool NormalizeToOne=true;//Set Compare mode first
  bool DoSave=true; //Save as pdf version
  bool IsCutFlow=false;
  bool DoRebin=true;

  char filename1[100]="../Ceres_looping/outfiles/4l1F/signal_selected.root";
  char filename2[100]="../Ceres_looping/outfiles/4l1F/bkg_selected.root"; //if you only want to draw one plot, use filename1 only

  char plotname1[100]="secondZMass";
  char plotname2[100]="secondZMass"; //if you only want to draw one plot, use plotname1 only

  char saveFileName[100]="plots/secondZMass.pdf";

  char Xtitle[100]="secondZMass(GeV)";
  char Ytitle[100]="entries";

  char legend1[100]="signal";
  char legend2[100]="all bkg";

  double minX=25; //if SetXRange
  double maxX=120; //if SetXRange
  double minY=0; //if SetYRange
  double maxY=1; //if SetYRange

  int RebinNum=2;

/******Main functions*******/
  TFile *file1 = new TFile(filename1);
  TH1D *h1=(TH1D *)file1->Get(plotname1);
  if(DoRebin) h1->Rebin(RebinNum);

  h1->SetBinContent(1, h1->GetBinContent(1) + h1->GetBinContent(0));
  h1->SetBinContent(h1->GetNbinsX(), h1->GetBinContent(h1->GetNbinsX()+1) + h1->GetBinContent(h1->GetNbinsX()));

  /*********SetPad********/
  double canvasYsize,padYsize;
  if(DoRatio) {canvasYsize=500; padYsize=0.3;} else {canvasYsize=500; padYsize=0;}
  TCanvas *canvas = new TCanvas("canvas","canvas",800,canvasYsize);
  TPad *pad1 = new TPad("pad1","pad1",0,padYsize,1.0,1.0); //Xbeginning,Ybeginning,Xending,Yending,100 per cent
  TPad *pad2 = new TPad("pad2","pad2",0,0,1.0,0.3);

  /*******SetCompare******/
  if(!Compare){
   if(!SetXRange) {minX=h1->GetXaxis()->GetBinLowEdge(1); maxX=h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins());}
   h1->GetXaxis()->SetRangeUser(minX,maxX);
   pad1->Draw();
   pad1->cd();
   if(IsCutFlow)
    h1->Draw("TEXT0 E0");
   else
    h1->Draw("E0");

   TLegend *legend = new TLegend(0.82,0.80,0.93,0.92); //the coordination of the legend frame;
   legend->AddEntry(h1,legend1,"lpfe");
   legend->SetTextFont(70);
   legend->SetTextSize(0.04);
   legend->Draw("same");
  }

  if(Compare){
   TFile *file2 = new TFile(filename2);
   TH1D *h2=(TH1D *)file2->Get(plotname2);
   if(DoRebin) h2->Rebin(RebinNum);
   h2->SetBinContent(1, h2->GetBinContent(1) + h2->GetBinContent(0));
   h2->SetBinContent(h2->GetNbinsX(), h2->GetBinContent(h2->GetNbinsX()+1) + h2->GetBinContent(h2->GetNbinsX()));

   /******Range******/
   if(!SetXRange){
    double minX1,minX2,maxX1,maxX2;
    minX1=h1->GetXaxis()->GetBinLowEdge(1);
    maxX1=h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins());
    minX2=h2->GetXaxis()->GetBinLowEdge(1);
    maxX2=h2->GetXaxis()->GetBinUpEdge(h2->GetXaxis()->GetNbins());
    if(minX1>minX2) minX=minX2;
    else minX=minX1;
    if(maxX1>maxX2) maxX=maxX1;
    else maxX=maxX2;
    } 
    h1->GetXaxis()->SetRangeUser(minX,maxX);
    h2->GetXaxis()->SetRangeUser(minX,maxX);

   if(!SetYRange){
    double minY1,minY2,maxY1,maxY2;
    minY1=h1->GetMinimum();
    maxY1=h1->GetMaximum();
    minY2=h2->GetMinimum();
    maxY2=h2->GetMaximum();
    if(minY1>minY2) minY=minY2;
    else minY=minY1;
    if(maxY1>maxY2) maxY=maxY1;
    else maxY=maxY2;
    }
    h1->GetYaxis()->SetRangeUser(minY,maxY);
    h2->GetYaxis()->SetRangeUser(minY,maxY);

   /******Normalize******/ 
   if(Normalize){
    double inte1=h1->Integral();
    double inte2=h2->Integral();
    h2->Scale(inte1/inte2);
   }

   if(NormalizeToOne){
    double inte1=h1->Integral();
    double inte2=h2->Integral();
    h1->Scale(1/inte1);
    h2->Scale(1/inte2);
   }

   /********SetPad********/
   if(DoRatio) pad1->SetBottomMargin(0); //the blank between pad1 and pad2 (if do ratio)
   pad1->SetTopMargin(0.05); //the blank on the top of the pad,100 per cent
   pad1->SetLeftMargin(0.15);
   pad1->SetRightMargin(0.05);
   pad1->SetGridx(); //the dashed grid
   pad1->SetGridy(); 
   pad1->Draw();
   pad1->cd(); //pad1 is the current pad
   if (IsCutFlow)
    {
     h1->Draw("TEXT0 E0");
     h2->Draw("TEXT0 E0 same"); 
    }
   else
    { 
     h1->Draw("E0");
     h2->Draw("E0 same");
    }

   TLegend *legend = new TLegend(0.82,0.80,0.93,0.92); //the coordination of the legend frame;
   legend->AddEntry(h1,legend1,"lpfe");
   legend->AddEntry(h2,legend2,"lpfe");
   legend->SetTextFont(70);
   legend->SetTextSize(0.04);
   legend->Draw("same");

   TH1D *h3;
   if(DoRatio){
    canvas -> cd(); 
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetLeftMargin(0.15);
    pad2->SetRightMargin(0.05);
    pad2->SetGridx();
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();
    h3 = (TH1D *)h1->Clone("h3");
    h3->Divide(h2);
    h3->Draw("E0");

  /*******h3 settings******/
  char Rationame[100];
  sprintf(Rationame,"%s/%s",legend1,legend2);
  h3->SetTitle(""); //Set ratio title blank
  h3->SetLineColor(kBlack);
  h3->SetLineWidth(2.0);
  h3->SetStats(0);  
  h3->GetXaxis()->SetTitle(Xtitle);
  h3->GetXaxis()->SetTitleSize(0.04);
  h3->GetXaxis()->SetTitleOffset(1);
  h3->GetXaxis()->SetTitleFont(70); //the thickness of the title
  h3->GetXaxis()->SetLabelSize(0.03);
  h3->GetXaxis()->SetLabelFont(70);
  h3->GetYaxis()->SetTitle(Rationame);
  h3->GetYaxis()->SetTitleSize(0.4);
  h3->GetYaxis()->SetTitleOffset(0.4);
  h3->GetYaxis()->SetTitleFont(70);
  h3->GetYaxis()->SetLabelSize(0.03);
  h3->GetYaxis()->SetLabelFont(70);
  }

  /*******h2 settings*******/
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2.0); //thick or thin of the line
  h2->SetStats(0); //remove the statistic frame

  }//compare

  /*******h1 settings******/
  h1->SetTitle("");
  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2.0);
  h1->SetStats(0);
  h1->GetXaxis()->SetTitle(Xtitle);
  h1->GetYaxis()->SetTitle(Ytitle);
  h1->GetYaxis()->SetTitleSize(0.04);
  h1->GetYaxis()->SetTitleOffset(1);
  h1->GetYaxis()->SetTitleFont(70);
  h1->GetYaxis()->SetLabelSize(0.03);
  h1->GetYaxis()->SetLabelFont(70);
  if(!Compare){
    h1->GetXaxis()->SetTitle(Xtitle);
    h1->GetXaxis()->SetTitleSize(0.04);
    h1->GetXaxis()->SetTitleOffset(1);
    h1->GetXaxis()->SetTitleFont(70); //the thickness of the title
    h1->GetXaxis()->SetLabelSize(0.03);
    h1->GetXaxis()->SetLabelFont(70);
  }

  if(DoSave){
    canvas->SaveAs(saveFileName);
  }

}
