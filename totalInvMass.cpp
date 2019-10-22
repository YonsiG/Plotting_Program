void totalInvMass()
{
   TFile *signalfile = new TFile("../Ceres_looping/outfiles/4l1F/signal_selected.root");
   TFile *WZfile = new TFile("../Ceres_looping/outfiles/4l1F/WZ_selected.root");
   TFile *hfile = new TFile("../Ceres_looping/outfiles/4l1F/h_selected.root");
   TFile *ZZfile = new TFile("../Ceres_looping/outfiles/4l1F/ZZ_selected.root");
   TFile *ttZfile = new TFile("../Ceres_looping/outfiles/4l1F/ttZ_selected.root");
   TFile *tWZfile = new TFile("../Ceres_looping/outfiles/4l1F/tWZ_selected.root");
   TFile *sttfile = new TFile("../Ceres_looping/outfiles/4l1F/stt_selected.root");
   TFile *othersfile = new TFile("../Ceres_looping/outfiles/4l1F/others_selected.root");

   TH1D* signalplot = (TH1D *)signalfile->Get("fatjetMass_lead");
   TH1D* WZplot = (TH1D *)WZfile->Get("fatjetMass_lead");
   TH1D* hplot = (TH1D *)hfile->Get("fatjetMass_lead");
   TH1D* ZZplot = (TH1D *)ZZfile->Get("fatjetMass_lead");
   TH1D* ttZplot = (TH1D *)ttZfile->Get("fatjetMass_lead");
   TH1D* tWZplot = (TH1D *)tWZfile->Get("fatjetMass_lead");
   TH1D* sttplot = (TH1D *)sttfile->Get("fatjetMass_lead");
   TH1D* othersplot = (TH1D *)othersfile->Get("fatjetMass_lead");

   signalplot->Scale(20);

   signalplot->Rebin(5);
   WZplot->Rebin(5);
   hplot->Rebin(5);
   ZZplot->Rebin(5);
   ttZplot->Rebin(5);
   tWZplot->Rebin(5);
   sttplot->Rebin(5);
   othersplot->Rebin(5);

   char  fileName[80] = ("total_plots.root");

   for(int ibin=1; ibin<signalplot->GetNbinsX()+1; ibin++)
    {
     WZplot->SetBinError(ibin,0);
     hplot->SetBinError(ibin,0);
     ZZplot->SetBinError(ibin,0);
     ttZplot->SetBinError(ibin,0);
     tWZplot->SetBinError(ibin,0);
     sttplot->SetBinError(ibin,0);
     othersplot->SetBinError(ibin,0);
    }

   WZplot->SetFillColor(2);
   hplot->SetFillColor(3);
   ZZplot->SetFillColor(4);
   ttZplot->SetFillColor(5);
   tWZplot->SetFillColor(6);
   sttplot->SetFillColor(7);
   othersplot->SetFillColor(8);

/****************N1T*****************/
   TCanvas *c = new TCanvas("plot1","",800,600);
   THStack* stack = new THStack("ts1","");
   c->SetMargin(0.1,0.05,0.1,0.05);

   signalplot->SetTitle("");
   signalplot->SetLineColor(kBlack);
   signalplot->SetMarkerStyle(20);
   signalplot->SetLineWidth(2.0);
   signalplot->SetStats(0);
   signalplot->GetYaxis()->SetTitle("Number of entries");
   signalplot->GetYaxis()->SetTitleSize(0.04);
   signalplot->GetYaxis()->SetTitleOffset(1);
   signalplot->GetYaxis()->SetTitleFont(70);
   signalplot->GetYaxis()->SetLabelSize(0.03);
   signalplot->GetYaxis()->SetLabelFont(70);
   signalplot->GetXaxis()->SetTitle("Invariant mass / GeV");
   signalplot->GetXaxis()->SetTitleSize(0.04);
   signalplot->GetXaxis()->SetTitleOffset(1);
   signalplot->GetXaxis()->SetTitleFont(70);
   signalplot->GetXaxis()->SetLabelSize(0.03);
   signalplot->GetXaxis()->SetLabelFont(70);

   signalplot->Draw("E");
   stack -> Add(ZZplot);
   stack -> Add(hplot);
   stack -> Add(ttZplot);
   stack -> Add(tWZplot);
   stack -> Add(sttplot);
   stack -> Add(WZplot);
   stack -> Add(othersplot);
   stack -> Draw("sameH");
   signalplot->Draw("sameE");

   TLegend *legend = new TLegend(0.73, 0.73, 0.95, 0.9);
   legend -> AddEntry(signalplot, "signal", "lpfe");
   legend -> AddEntry(WZplot, "WZ", "f");
   legend -> AddEntry(hplot, "h", "f");
   legend -> AddEntry(ZZplot, "ZZ", "f");
   legend -> AddEntry(ttZplot, "ttZ", "f");
   legend -> AddEntry(tWZplot, "tWZ", "f");
   legend -> AddEntry(sttplot, "stt", "f");
   legend -> AddEntry(othersplot, "others","f");
   legend -> SetTextFont(20);
   legend -> SetTextSize(0.035);
   legend -> SetBorderSize(0);
   legend -> Draw("same");
//   legend -> SetHeader("ATLAS Internal");

   string histName = "VisMasstotal";
   c->SaveAs(("figures/"+histName+"result.png").c_str());  //save plots to disk

/*   TFile *file = new TFile(fileName,"RECREATE");
   TH1D *Mass=(TH1D *)signalplot->Clone();
   Mass->Add(WZplot,-1);
   Mass->Add(hplot,-1);
   Mass->Add(ZZplot,-1);
   Mass->Add(ttZplot,-1);
   Mass->Add(tWZplot,-1);
   Mass->Add(sttplot,-1);
   file->Write();
   file->Close();
*/
}
