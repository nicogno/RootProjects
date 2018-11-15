{
    #define ndata 13
    
    //TFormula *tf = new TFormula("","((x-10000)/x)*y/10000");    //
    
    TCanvas *c1 = new TCanvas("c1","Taratura soglia discriminatore",1200,600);
    double x[ndata], y[ndata], mean, max = 0, min = 1, ex[ndata], ey[ndata];
    
    x[0] = -22;
    y[0] = 3983.4;
    x[1] = -50;
    y[1] = 67.1;
    x[2] = -70;
    y[2] = 63.9;
    x[3] = -90;
    y[3] = 59.6;
    x[4] = -110;
    y[4] = 59.1;
    x[5] = -130;
    y[5] = 54;
    x[6] = -150;
    y[6] = 57.5;
    x[7] = -170;
    y[7] = 56.1;
    x[8] = -190;
    y[8] = 57.3;
    x[9] = -210;
    y[9] = 54.4;
    x[10] = -230;
    y[10] = 53.9;
    x[11] = -250;
    y[11] = 59.1;
    x[12] = -262;
    y[12] = 53.4;
    
    for(int i=0; i<ndata; i++) {
        ex[i] = 0.;
        ey[i] = 0.;
    }
    
    //Settings grafico con errori
    gr = new TGraphErrors(ndata,x,y,ex,ey);
    gr->SetTitle("Taratura soglia discriminatore;Vth (mV); # conteggi");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->Draw("AP*");
    
    
    /*
    //Settings linea orizzontale valore medio
    TLine *meanLine = new TLine(0.8,mean,8.2,mean);
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
    c1->SaveAs("Curva_taratura_discriminatore.pdf","pdf");
}

