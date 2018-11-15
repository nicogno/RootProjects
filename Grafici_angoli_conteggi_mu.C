{

  TCanvas *c1 = new TCanvas("c1","Grafico mu vs angoli", 1600, 1200);
 

  const int n = 15;
  double angoli[n];
  double err_angoli[n]={2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
  double mean[n]={664.9,658.3,654,655,654.6,654,654.4,654.7,654.3,654.9,654.6,653.8,655.5,660.6,662.5};
  double error_mean[n]={1.0,1.2,0.8,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.7,1.1,1.7};
  double counts[n]={14.39,15.48,35.67,188.2,811,958.6,1511,1807,1560,985,761.2,216.1,31.09,18.4,16.65};
  double error_counts[n]={0.68,0.85,1.63,4.9,8.7,8.8,10.9,12.0,8.9,9.2,8.2,4.6,1.41,1.0,0.86};

  angoli[0]=-35;

  for(int i = 0; i<15; i++)
    {
      angoli[i+1]=angoli[i]+5;
      //cout<<angoli[i]<<endl;
    }

  gr1 = new TGraphErrors(n,angoli,mean,err_angoli,error_mean);

    gr1->SetTitle("CH vs Angoli;Theta (^{ o });CH");
  gr1->SetMarkerColor(4);
  gr1->SetMarkerStyle(21);
  gr1->Draw();
  
  c1->SaveAs("Grafico_Mu_vs_angoli.pdf",".pdf");
  c1->SaveAs("Grafico_Mu_vs_angoli.root",".root");

  TCanvas *c2 = new TCanvas("c2","Conteggi vs angoli", 1600, 1200);

  gr2 = new TGraphErrors(n,angoli,counts,err_angoli,error_counts);

    gr2->SetTitle("Counteggi vs Angoli;Theta (^{ o });Counts");
  gr2->SetMarkerColor(4);
  gr2->SetMarkerStyle(21);
  gr2->Draw("ALP");
  
  c2->SaveAs("Grafico_Counts_vs_angoli.pdf",".pdf");
  c2->SaveAs("Grafico_Counts_vs_angoli.root",".root");

}
