{
    
    ifstream in;
    
    Int_t x,y,z;
    Int_t nlines = 0;
    int nbins;
    int k = 0, j = 0, binmin = 0, binmax = 0;
    double xmax, xmin;
    TCanvas *c1 = new TCanvas("c1","Test Canvas", 1200, 600);
        
    in.open("TDCsingolaCH1RitardoStart46,5.dat");
    x = 0, y = 0, z = 0, nlines = 0;
    
    TH1D *h1 = new TH1D("Graph and Fit parameters","Prova TDC 46",1000,0,1000);


    while (1) {
        in >> x >> y >> z ;
        in.ignore(100,'\n');
        if (!in.good()) break;
        h1->Fill(y);
        nlines++;
    }
    h1->Fit("gaus");

    gStyle->SetOptFit(0111);
    gStyle->SetOptStat(1111);

    nbins = h1 -> GetNbinsX();
    k = 0, j = 0, binmin = 0, binmax = 0;

    while(j < nbins && k == 0) {
        if (h1->GetBinContent(j) > 0) {
            binmin = j;
            k = 1;
        }
        j++;
    }

    j = nbins, k = 0;

    while(j > 0 && k == 0) {
        if (h1->GetBinContent(j) > 0) {
            binmax = j;
            k = 1;
        }
        j--;
    }

    xmax = (h1->GetXaxis()->GetBinCenter(binmax)) + 5;
    xmin = (h1->GetXaxis()->GetBinCenter(binmin)) - 5;
    h1->GetXaxis()->SetRangeUser(xmin, xmax);

    cout << "xmin = " << xmin << ", xmax = " << xmax << endl;
    cout << "binmin = " << binmin << ", binmax = " << binmax << endl;
    
    
    h1->SetMaximum((h1->GetFunction("gaus")->GetParameter(0))+10);

    h1->Draw("h");


    c1->SaveAs("Prova_TDC_46.pdf","pdf");
    
    in.close();
}

