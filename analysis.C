{
    
    ifstream in;
    
    Double_t col1, col2;  //Identificativi colonne per input file .dat
    Double_t noisePercentage2[100], networkError2[100], noisePercentage3[100], networkError3[100], noisePercentage4[100], networkError4[100], noisePercentage5[100], networkError5[100];
    
    Int_t nlines = 0;
    in.open("data2.dat");
    
    while (1) {
        in >> col1 >> col2;
        in.ignore(100,'\n');
        if (!in.good()) break;
        noisePercentage2[nlines] = col1;
        networkError2[nlines] = col2;
        nlines++;
    }
    in.close();
    
    in.open("data3.dat");
    nlines = 0;
    while (1) {
        in >> col1 >> col2;
        in.ignore(100,'\n');
        if (!in.good()) break;
        noisePercentage3[nlines] = col1;
        networkError3[nlines] = col2;
        nlines++;
    }
    in.close();
    
    in.open("data4.dat");
    nlines = 0;
    while (1) {
        in >> col1 >> col2;
        in.ignore(100,'\n');
        if (!in.good()) break;
        noisePercentage4[nlines] = col1;
        networkError4[nlines] = col2;
        nlines++;
    }
    in.close();
    
    in.open("data5.dat");
    nlines = 0;
    while (1) {
        in >> col1 >> col2;
        in.ignore(100,'\n');
        if (!in.good()) break;
        noisePercentage5[nlines] = col1;
        networkError5[nlines] = col2;
        nlines++;
    }
    in.close();
    
    TCanvas *c1 = new TCanvas("c1","Hopfield errors comparison",1600, 1600);
    c1->SetGrid();
    
    Int_t n = 100;
    
    TGraph* gr2 = new TGraph(n,noisePercentage2,networkError2);
    gr2->SetMarkerColor(2);
    gr2->SetMarkerStyle(21);
    TGraph* gr3 = new TGraph(n,noisePercentage3,networkError3);
    gr3->SetMarkerColor(3);
    gr3->SetMarkerStyle(21);
    TGraph* gr4 = new TGraph(n,noisePercentage4,networkError4);
    gr4->SetMarkerColor(4);
    gr4->SetMarkerStyle(21);
    TGraph* gr5 = new TGraph(n,noisePercentage5,networkError5);
    gr5->SetMarkerColor(6);
    gr5->SetMarkerStyle(21);
    
    gr2->SetTitle("Hopfield network accuracy (alfa = 0.08); Noise percentage; Network percentage error");
    gr3->SetTitle("Hopfield network accuracy (alfa = 0.12); Noise percentage; Network percentage error");
    gr4->SetTitle("Hopfield network accuracy (alfa = 0.16); Noise percentage; Network percentage error");
    gr5->SetTitle("Hopfield network accuracy (alfa = 0.20); Noise percentage; Network percentage error");
    
    gStyle->SetTitleFontSize(.08);
    
    gr2->GetXaxis()->SetTitleSize(.05);
    gr2->GetYaxis()->SetTitleSize(.06);
    gr3->GetXaxis()->SetTitleSize(.05);
    gr3->GetYaxis()->SetTitleSize(.06);
    gr4->GetXaxis()->SetTitleSize(.05);
    gr4->GetYaxis()->SetTitleSize(.06);
    gr5->GetXaxis()->SetTitleSize(.05);
    gr5->GetYaxis()->SetTitleSize(.06);


    c1->Divide(2,2);
    
    c1->cd(1);
    gr2->Draw("AC*");
    
    c1->cd(2);
    gr3->Draw("AC*");
    
    c1->cd(3);
    gr4->Draw("AC*");
    
    c1->cd(4);
    gr5->Draw("AC*");

    c1->SetGrid();
    c1->GetFrame()->SetFillColor(21);
    c1->GetFrame()->SetBorderSize(12);
    c1->Update();
    c1->SaveAs("Hopfield_errors_comparison.pdf","pdf");
}


