{\rtf1\ansi\ansicpg932\cocoartf2708
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 TH1D* takeLi(TString option,int gate_option,int runnumber)\{//"up""down"option\uc0\u27083 \u36896 \u12395 \u12391 \u12365 \u12394 \u12356 \u12363 \u12394 \u12540 \u12390 \u12356 \u12358 \
  int runnum = 0;\
  TH1D *h;\
  TFile *file=new TFile(Form("outroot/%s/hist_run_0%d_000.root",option.Data(),runnumber));//\uc0\u12371 \u12371 \u12391 root\u12501 \u12449 \u12452 \u12523 \u12434 \u27770 \u12417 \u12427 //option.Data()\u12387 \u12390 \u12356 \u12358 \u12398 \u12399 option\u12434 char*\u12395 \u22793 \u12360 \u12390 \
  TDirectory *dir = file->GetDirectory(Form("hTOF_Li%d_gate",gate_option));//ROOT\uc0\u12501 \u12449 \u12452 \u12523 \u20013 \u12395 \u12487 \u12451 \u12524 \u12463 \u12488 \u12522 \u12364 \u12394 \u12369 \u12428 \u12400 \u12371 \u12371 \u12399 \u12467 \u12513 \u12531 \u12488 \u12450 \u12454 \u12488 \
  h=(TH1D*)dir->Get(Form("hTOF_Li%d_gate_d%d",gate_option,gate_option+6));//\uc0\u12371 \u12371 \u12399 file\u12363 \u12425 get\u12391 \u12362 \u12369 \u12384 \u12392 \u24605 \u12358 \
  return h;\
\}}