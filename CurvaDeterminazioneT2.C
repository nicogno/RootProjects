{
    #define ndata 17
    
    //TFormula *tf = new TFormula("","((x-10000)/x)*y/10000");    //
    
    gStyle->SetOptFit(1111);
    TCanvas *c1 = new TCanvas("c1","Curva determinazione T2",1200,600);
    
    float tempo[ndata] = {10,
        20,
        30,
        40,
        50,
        60,
        70,
        80,
        100,
        120,
        140,
        160,
        170,
        180,
        190,
        200,
        210
    };
    float amplitude[ndata] = {41.4,
        36.7,
        29.7,
        25,
        18.4,
        15.1,
        14,
        13,
        9.3,
        7.1,
        5.3,
        3.9,
        3.3,
        2.9,
        2.3,
        2.1,
        1.8
    };
    float eTempo[ndata] = { };
    float eAmplitude[ndata] = {0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1,
        0.1
    };
    
    //Settings grafico con errori
    TGraphErrors *gr = new TGraphErrors(ndata,tempo,amplitude,eTempo,eAmplitude);
    gr->SetTitle("Curva determinazione T2;Tempo (ms); Amplitude (%)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    TF1 *fitExpo = new TF1("fitExpo","[0]*exp(-x/[1])", 0, 230);
    fitExpo->SetParameters(1,1);
    fitExpo->SetParNames ("Constant","T2");
    gr->Fit(fitSeno, "R");
    gr->Draw("AP*");
    
    /*
    //Settings linee valore max
    TLine *meanLine = new TLine(0,88.4,19.93,88.4);
    meanLine->SetLineColor(kRed);
    meanLine->SetLineWidth(3);
    meanLine->SetLineStyle(10);
    meanLine->Draw("SAME");
    
    
    //Settings box in alto a destra per legenda
    TLatex box(5.9,0.053,"#color[2]{Mean value = (0.042 #pm 0.005) s}");
    box.SetTextSize(0.04);
    box.Draw("SAME");
    */
    
    //Settings generali canvas
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Update();
    c1->SaveAs("Ampiezza_vs_Durata.pdf","pdf");
}

