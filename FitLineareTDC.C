{
    
    Int_t n = 7;
    Double_t x1[7], x2[7], t1[7], t2[7], ex1[7], ex2[7], ey1[7], ey2[7], CHtoSEC = 0.25*TMath::Power(10,-9); ;
    
    
    x1[0] = -46.5 * TMath::Power(10,-9);
    x1[1] = -31. * TMath::Power(10,-9);
    x1[2] = -15.5 * TMath::Power(10,-9);
    x1[3] = 0.;
    x1[4] = 15.5 * TMath::Power(10,-9);
    x1[5] = 31. * TMath::Power(10,-9);
    x1[6] = 46.5 * TMath::Power(10,-9);
    
    x2[0] = -46.5 * TMath::Power(10,-9);
    x2[1] = -31. * TMath::Power(10,-9);
    x2[2] = -15.5 * TMath::Power(10,-9);
    x2[3] = 0.;
    x2[4] = 15.5 * TMath::Power(10,-9);
    x2[5] = 31. * TMath::Power(10,-9);
    x2[6] = 46.5 * TMath::Power(10,-9);
    
    for(int i = 0; i < n; i++) {
        ex1[i] = 1 * TMath::Power(10,-9);
        ex2[i] = 1 * TMath::Power(10,-9);
    }
    
    t1[0] = 207.3 * CHtoSEC;
    t1[1] = 265.1 * CHtoSEC;
    t1[2] = 322.5 * CHtoSEC;
    t1[3] = 379.7 * CHtoSEC;
    t1[4] = 442.4 * CHtoSEC;
    t1[5] = 506.8 * CHtoSEC;
    t1[6] = 573.5 * CHtoSEC;
    
    t2[0] = 225.8 * CHtoSEC;
    t2[1] = 286.4 * CHtoSEC;
    t2[2] = 345.7 * CHtoSEC;
    t2[3] = 405.3 * CHtoSEC;
    t2[4] = 471.1 * CHtoSEC;
    t2[5] = 540.5 * CHtoSEC;
    t2[6] = 610.9 * CHtoSEC;
    
    ey1[0] = 0.6505 * CHtoSEC;
    ey1[1] = 0.6118 * CHtoSEC;
    ey1[2] = 0.6204 * CHtoSEC;
    ey1[3] = 0.6443 * CHtoSEC;
    ey1[4] = 0.6154 * CHtoSEC;
    ey1[5] = 0.6390 * CHtoSEC;
    ey1[6] = 0.6488 * CHtoSEC;
    
    ey2[0] = 0.7242 * CHtoSEC;
    ey2[1] = 0.6705 * CHtoSEC;
    ey2[2] = 0.7373 * CHtoSEC;
    ey2[3] = 0.7027 * CHtoSEC;
    ey2[4] = 0.6701 * CHtoSEC;
    ey2[5] = 0.6873 * CHtoSEC;
    ey2[6] = 0.6807 * CHtoSEC;
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    
    
    TGraphErrors *gr1 = new TGraphErrors(n,x1,t1,ex1,ey1);
    TGraphErrors *gr2 = new TGraphErrors(n,x2,t2,ex2,ey2);
    gr1->SetTitle("CH1 linear fit;Delay (s);TDC Time (s)");
    gr2->SetTitle("CH2 linear fit;Delay (s);TDC Time (s)");
    
    TCanvas *c1 = new TCanvas("c1","TDC CH1 Linear response", 600, 400);

    TF1 *f1 = new TF1("f1","pol1",-46.5,46.5);
    f1->SetParNames("Constant", "Slope");
    gr1->Fit("f1");
    gr1->Draw();
    
    
    //Stats box editing
    c1->Update();
    TPaveStats *ps1 = (TPaveStats*)c1->GetPrimitive("stats");
    ps1->SetX1NDC(0.20);
    ps1->SetX2NDC(0.50);
    ps1->SetY1NDC(0.60);
    ps1->SetY2NDC(0.85);
   
    string text1 = std::string("Linear correlation factor = ") + to_string(gr1->GetCorrelationFactor());
    const char *correlationFactor1 =  text1.c_str();
    
    TList *list1 = ps1->GetListOfLines();
    TLatex *myt1 = new TLatex(0,0,correlationFactor1);
    myt1->SetTextFont(43);
    myt1->SetTextSize(11);
    list1->Add(myt1);
    
    ps1->DrawClone();
    c1->Modified();
    ////////////////////
    
    c1->SaveAs("TDC Linear Fit CH1.pdf","pdf");
    
    TCanvas *c2 = new TCanvas("c2","TDC CH2 Linear response", 600, 400);
    
    TF1 *f2 = new TF1("f2","pol1",-46.5,46.5);
    f2->SetParNames("Constant", "Slope");
    gr2->Fit("f2");
    gr2->Draw();
    
    //Stats box editing
    c2->Update();
    TPaveStats *ps2 = (TPaveStats*)c2->GetPrimitive("stats");
    ps2->SetX1NDC(0.20);
    ps2->SetX2NDC(0.50);
    ps2->SetY1NDC(0.60);
    ps2->SetY2NDC(0.85);
    
    string text2 = std::string("Linear correlation factor = ") + to_string(gr2->GetCorrelationFactor());
    const char *correlationFactor2 =  text2.c_str();
    
    TList *list2 = ps2->GetListOfLines();
    TLatex *myt2 = new TLatex(0,0,correlationFactor2);
    myt2->SetTextFont(43);
    myt2->SetTextSize(11);
    list2->Add(myt2);
    
    ps2->DrawClone();
    c2->Modified();
    ////////////////////
    
    c2->SaveAs("TDC Linear Fit CH2.pdf","pdf");
    
}


