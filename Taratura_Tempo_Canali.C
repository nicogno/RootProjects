//Macro usata per la determinazione numerica e grafica dei tempi morti dell'elettronica
{
    TCanvas *c1 = new TCanvas("c1","Conversione canali - tempo",1600,1200);
    
    Int_t n = 5;
    Double_t x[5], y[5], ex[5], ey[5];
    
    y[0] = 0.;
    y[1] = 0.25;
    y[2] = 0.50;
    y[3] = 0.75;
    y[4] = 1.;
    
    ey[0] = 0.01;
    ey[1] = 0.01;
    ey[2] = 0.01;
    ey[3] = 0.01;
    ey[4] = 0.01;
    
    x[0] = 456.2;
    x[1] = 506;
    x[2] = 555.4;
    x[3] = 604.9;
    x[4] = 654.7;
    
    ex[0] = 0.1;
    ex[1] = 0.1;
    ex[2] = 0.1;
    ex[3] = 0.1;
    ex[4] = 0.;
    
    gStyle->SetOptFit(01111);
    gStyle->SetOptStat("rRmMen");
    gStyle->SetStatH(0.07); gStyle->SetStatW(0.25);
    gStyle->SetStatX(0.57); gStyle->SetStatY(0.8);
    
    gr = new TGraphErrors(n,x,y,ex,ey);
    gr->SetTitle("Conversione Canali - Tempo; CH No.; Delay (#muS)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    
    
    TF1 *linearFit = new TF1("linearFit","pol1",340,891);
    linearFit->SetParNames("Intercept", "Time (#muS)/CH");
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
    
    c1->SaveAs("Taratura_Tempo_Canali.pdf","pdf");
}

