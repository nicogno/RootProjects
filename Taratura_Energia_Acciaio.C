//Macro usata per la determinazione numerica e grafica dei tempi morti dell'elettronica
{
    TCanvas *c1 = new TCanvas("c1","Conversione canali - energia",1600,1200);
    
    Int_t n = 3;
    Double_t x[3], y[3], ex[3], ey[3];
    
    y[0] = 511;
    y[1] = 1173.2;
    y[2] = 1332.5;
    
    ey[0] = 1;
    ey[1] = 1;
    ey[2] = 1;
    
    x[0] = 340.6;
    x[1] = 782.4;
    x[2] = 890.2;
    
    ex[0] = 0.;
    ex[1] = 0.4;
    ex[2] = 0.5;
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    gStyle->SetStatH(0.07); gStyle->SetStatW(0.25);
    gStyle->SetStatX(0.57); gStyle->SetStatY(0.8);
    
    gr = new TGraphErrors(n,x,y,ex,ey);
    gr->SetTitle("Conversione Canali - Energia; CH No.; Energy (KeV)");
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
    
    c1->SaveAs("Taratura_Energia_Acciaio.pdf","pdf");
}

