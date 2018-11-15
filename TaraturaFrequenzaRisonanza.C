{
    #define ndata 25
    
    //TFormula *tf = new TFormula("","((x-10000)/x)*y/10000");    //
    
    TCanvas *c1 = new TCanvas("c1","Taratura soglia discriminatore",1200,600);
    
    float frequency[ndata] = {19.00000,19.5,19.7,19.80000,19.90000,19.91000,19.92000,19.92500,19.92900,19.92950,19.92999,19.929999,19.93000,19.930001,19.93001,19.93050,19.93100,19.93500,19.94000,19.95000,19.96000,20.00000,20.10000,20.5,21.00000};
    float amplitude[ndata] = {0.003,5.44,9.84,10.38,83.3,87.2,87.9,88.2,88.3,88.3,88.3,88.3,88.4,88.3,88.3,88.3,88.3,88.3,88.2,87.8,87.2,76.3,13.05,0.54,0.15};
    float eFrequency[ndata] = { };
    float eAmplitude[ndata] = {0.006,0.02,0.03,0.04,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.03,0.02,0.02};
    
    //Settings grafico con errori
    TGraphErrors *gr = new TGraphErrors(ndata,frequency,amplitude,eFrequency,eAmplitude);
    gr->SetTitle("Taratura frequenza risonanza;Frequency (MHz); Amplitude (%)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    TF1 *fit1 = new TF1("fit1","pol2", 19.85, 20.02);
    gr->Fit(fit1, "R");
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
    c1->SaveAs("Curva_taratura_frequenza_risonanza.pdf","pdf");
}

