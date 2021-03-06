{
    
    ifstream in;
    
    Int_t rownumber , ch0 , ch1 , ch2 , ch3 , ch4 , ch5 , ch6 , ch7 , ch8;  //Identificativi colonne per input file .dat
    Int_t nlines = 0;
    int nbins;
    int k = 0, j = 0, binmin = 0, binmax = 0;
    double xmax, xmin;
    TCanvas *c1 = new TCanvas("c1","ADC CH2", 1600, 1600);
    
    in.open("ADCsingoleCH2-modificasoglia.dat");

    TH1D *h1 = new TH1D("Gauss fit parameters","Background;ADC Channels;Counts",1000,0,250);
    TH1D *h2 = new TH1D("Landau fit parameters","Signal;ADC Channels;Counts",1000,0,1800);
    TH1D *h3 = new TH1D("Gauss fit parameters","Pedestal;ADC Channels;Counts",1000,0,100);
    
    
    while (1) {
        in >> rownumber >> ch0 >> ch1 >> ch2 >> ch3 >> ch4 >> ch5 >> ch6 >> ch7 >> ch8 ;
        in.ignore(100,'\n');
        if (!in.good()) break;
        if ( ch2 < 167) {
            h1->Fill(ch2);
        } else {
            h2->Fill(ch2);
        }
        h3->Fill(ch1);
        h3->Fill(ch3);
        h3->Fill(ch4);
        h3->Fill(ch5);
        h3->Fill(ch6);
        h3->Fill(ch7);
        h3->Fill(ch8);
        nlines++;
    }
    in.close();
    
    gStyle->SetOptFit(0111);
    gStyle->SetOptStat(1111);

    c1->Divide(2,2);
    
    c1->cd(1);          //////////////////////
    h1->Fit("gaus");
    h1->GetFunction("gaus")->SetLineColor(2);
    h1->GetFunction("gaus")->SetLineWidth(3);
    h1->DrawCopy("","");
    c1->cd(2);          //////////////////////
    h2->Fit("landau");
    h2->GetFunction("landau")->SetLineColor(3);
    h2->GetFunction("landau")->SetLineWidth(3);
    h2->DrawCopy("","");
    c1->cd(3);          //////////////////////
    h3->Fit("gaus");
    h3->GetFunction("gaus")->SetLineColor(6);
    h3->GetFunction("gaus")->SetLineWidth(3);
    h3->DrawCopy("","");
    c1->cd(4);          //////////////////////
    TH1 *frame = c1->DrawFrame(0,0,1800,6000,"Pedestal + Signal;ADC Channels;Counts");
    c1->SetLogy();
    c1->Update();
    h3->Draw("SAME");
    h2->Draw("SAME");
    c1->SaveAs("ADC CH2.pdf","pdf");
}

