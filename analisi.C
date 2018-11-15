{
    TCanvas *c1 = new TCanvas("c1","Centroidi e FWHM vs HV",200,10,1400,1000);
    Double_t x[17], y2[17];
    Int_t j = 0, n = 17;
    
    c1->Divide(2,1);
    
    TGraph* gr1 = new TGraph("centroidi.dat");
    
    c1->cd(1);
    gr1->Draw("A*");
    
    TGraph* gr2 = new TGraph("fwhm.dat");
    
    c1->cd(2);
    gr2->Draw("A*");
    c1->SaveAs("Centroidi+FWHMvsHV.pdf",".pdf");
    c1->SaveAs("Centroidi+FWHMvsHV.root",".root");
}
