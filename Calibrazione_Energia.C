//Macro usata per la determinazione numerica e grafica dei tempi morti dell'elettronica
{
    TCanvas *c1 = new TCanvas("c1","Calibrazione energia",1600,1200);
    
    Int_t n = 3;
    Double_t x[3], y[3], ex[3], ey[3];
    
    y[0] = 4788;
    y[1] = 5490;
    y[2] = 5810;
    
    ey[0] = 0.;
    ey[1] = 0.;
    ey[2] = 0.;
    
    x[0] = 660.5;
    x[1] = 758.7;
    x[2] = 802.8;
    
    ex[0] = 0.2;
    ex[1] = 0.2;
    ex[2] = 0.2;
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    gStyle->SetStatH(0.07); gStyle->SetStatW(0.25);
    gStyle->SetStatX(0.57); gStyle->SetStatY(0.8);
    
    gr = new TGraphErrors(n,x,y,ex,ey);
    gr->SetTitle("Calibrazione Energia; CH No.; Energy (KeV)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    
    
    TF1 *linearFit = new TF1("linearFit","pol1",340,891);
    linearFit->SetParNames("Intercept", "Energy (KeV)/CH");
    linearFit->SetParameters(1,1);
    
    gr->Fit("linearFit");
    gr->Draw("AP*");

    //Stats box editing
    c1->Update();
    TPaveStats *ps2 = (TPaveStats*)c1->GetPrimitive("stats");
    string text2 = std::string("Linear correlation factor = ") + to_string(gr->GetCorrelationFactor());
    const char *correlationFactor2 =  text2.c_str();
    
    TList *list2 = ps2->GetListOfLines();
    TLatex *myt2 = new TLatex(0,0,correlationFactor2);
    myt2->SetTextFont(43);
    myt2->SetTextSize(35);
    list2->Add(myt2);
    
    ps2->DrawClone();
    c1->Modified();
    
    c1->SaveAs("Calibrazione_Energia.pdf","pdf");
}

