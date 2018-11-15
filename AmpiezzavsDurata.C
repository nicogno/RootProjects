{
    #define ndata 37
    
    //TFormula *tf = new TFormula("","((x-10000)/x)*y/10000");    //
    
    gStyle->SetOptFit(1111);
    TCanvas *c1 = new TCanvas("c1","Taratura soglia discriminatore",1200,600);
    
    float tempo[ndata] = {1.5,
        1.6,
        1.7,
        1.8,
        2,
        2.5,
        3,
        3.5,
        4,
        4.5,
        5,
        5.5,
        6,
        6.5,
        7,
        7.5,
        8,
        8.5,
        9,
        9.5,
        10,
        10.5,
        11,
        11.5,
        12,
        12.5,
        13,
        13.5,
        14,
        14.5,
        15,
        15.5,
        16,
        16.5,
        17,
        17.5,
        18};
    float amplitude[ndata] = {23.55,
        24.9,
        26.72,
        28.23,
        31.39,
        38.96,
        45.89,
        52.44,
        58.23,
        62.6,
        67.82,
        71.58,
        74.58,
        76.87,
        78.31,
        79.14,
        78.54,
        77.88,
        75.46,
        73.03,
        70.57,
        67.01,
        62.85,
        57.76,
        52.65,
        46.75,
        40.85,
        34.32,
        27.91,
        21.68,
        16.92,
        13.28,
        11.97,
        14,
        18.33,
        23.7,
        29.3};
    float eDurata[ndata] = { };
    float eAmplitude[ndata] = {0.03,
        0.04,
        0.04,
        0.04,
        0.04,
        0.05,
        0.06,
        0.07,
        0.08,
        0.08,
        0.09,
        0.09,
        0.1,
        0.1,
        0.1,
        0.1,
        0.09,
        0.09,
        0.08,
        0.08,
        0.07,
        0.07,
        0.06,
        0.05,
        0.05,
        0.04,
        0.04,
        0.03,
        0.04,
        0.04,
        0.05,
        0.07,
        0.09,
        0.1,
        0.1,
        0.1,
        0.1};
    
    //Settings grafico con errori
    TGraphErrors *gr = new TGraphErrors(ndata,durata,amplitude,eDurata,eAmplitude);
    gr->SetTitle("Ampiezza vs Durata;Durata (us); Amplitude (%)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    TF1 *fitSeno = new TF1("fitSeno","[0]*sin([1]*x)", 0, 10);
    fitSeno->SetParameters(80,0.5);
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

