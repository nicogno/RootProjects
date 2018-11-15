//Macro usata per la determinazione numerica e grafica dei tempi morti dell'elettronica
{
    TFormula *tf = new TFormula("","((x-10000)/x)*y/10000");    //Formula per calcolare tempo morto
    
    TCanvas *c1 = new TCanvas("c1","Dead time distribution",1200,600);
    double x[8], y[8], mean, max = 0, min = 1, ex[8], ey[8];    //x array per il numero del canale in esame, y per il corrispondente tempo morto, ex ed ey errori corrispondenti, mean meadia, man e min variabili che userò per determinare il max ed il min di y[]
    int n = 8;                      //Numero scintillatori
    
    x[0] = 1;                        //Fill degli array
    y[0] = tf->Eval(53175, 473);    //Valuto la relazione sopra con i dati degli 8 scintillatori
    x[1] = 2;
    y[1] = tf->Eval(66199, 431);
    x[2] = 3;
    y[2] = tf->Eval(52713, 486);
    x[3] = 4;
    y[3] = tf->Eval(71874, 479);
    x[4] = 5;
    y[4] = tf->Eval(76584, 543);
    x[5] = 6;
    y[5] = tf->Eval(54189, 474);
    x[6] = 7;
    y[6] = tf->Eval(79607, 533);
    x[7] = 8;
    y[7] = tf->Eval(65838, 549);
    
    for(int channel=0; channel<n; channel++) {                    //Calcolo max e min tempi morti per semidispersione massima che uso come            errore
        mean += y[channel];
        if(y[channel]>max) {
            max = y[channel];
        }
        if(y[channel]<min) {
            min = y[channel];
        }
    }
    
    mean = mean/n;      //Calcolo valore medio
    double_t msd = (max - min)/2;   //Calcolo semidispersione massima
    string msdConstant = to_string(msd);    //Converto semidispersione massima in stringa da usare su grafico

    for(int channel = 0; channel<n; channel++) {
        ex[channel] = 0;
        ey[channel] = msd;
    }
    
    //Settings grafico con errori
    gr = new TGraphErrors(n,x,y,ex,ey);
    gr->SetTitle("Dead Time distribution;Channel No.; Dead time (s)");
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->Draw("AP*");
    
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
    
    //Settings generali canvas
    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Update();
    c1->SaveAs("Dead Time distribution.pdf","pdf");
}

