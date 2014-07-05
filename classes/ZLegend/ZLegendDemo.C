// name: ZLegendDemo.C
// date: 04 Jul 14
// auth: Zach Hartwig
// desc: Demo showing how to use modified TLegend class to color
//       the TLegend text labels
//
//       The key is a new arguments to AddEntry method that allows
//       user to pass a color value for the object text:
//         
//       TLegend::AddEntry(TObject *GraphicalObject,
//                         Int_t Color,
//                         const char *title,
//                         const char *options)
//                         
{
  const Int_t n = 5;
  const Double_t x[n] = {1,2,3,4,5};
  const Double_t y1[n] = {1,3,9,16,25};
  const Double_t y2[n] = {1,3,5,7,9};

  c = new TCanvas("c","c",0,0,500,500);

  g = new TGraph(n,x,y1);
  g->SetLineColor(2);
  g->SetLineWidth(2);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(2);
  g->SetMarkerColor(2);
  g->Draw("ALP");

  h = new TGraph(n,x,y2);
  h->SetLineColor(4);
  h->SetLineWidth(2);
  h->SetMarkerStyle(22);
  h->SetMarkerSize(2);
  h->SetMarkerColor(4);
  h->Draw("LP");

  l = new ZLegend(0.2, 0.5, 0.5, 0.8);
  l->AddEntry(g,2,"A graph","lp");
  l->AddEntry(h,4,"A graph","lp");
  l->SetFillColor(18);
  l->Draw();

  c->Update();
}
