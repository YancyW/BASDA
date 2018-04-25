#include "TLatex.h"
#include "TPDF.h"
#include "TPostScript.h"

#include "TROOT.h"
#include "TCanvas.h"
#include "TImage.h"

void merge() {
   // create an image from PS file
   TPDF ps("input.pdf",-111);

   TCanvas *c6 = new TCanvas("psexam", "Example how to display PS file in canvas", 600, 400);
   TLatex *tex = new TLatex(0.06,0.9,"The picture below has been loaded from a PS file:");
   tex->Draw();

   TPad *eps = new TPad("eps", "eps", 0., 0., 1., 0.75);
   eps->Draw();
   eps->cd();
   ps.Draw("xxx");

   TImage *img = TImage::Open("ILD-logo.jpg");

   if (!img) {
      printf("Could not create an image... exit\n");
      return;
   }
   TPad *l = new TPad("l","l",0.,0.9,0.1,1.);
   //gPad->cd(0);
   l->Draw();
   l->cd();
   img->Draw();
}


