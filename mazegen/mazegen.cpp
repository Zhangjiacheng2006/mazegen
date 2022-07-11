#include "mazegen.h"
#include "./ui_mazegen.h"

mazegen::mazegen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mazegen)
{
    ui->setupUi(this);

}

mazegen::~mazegen(){
    delete ui;
}
#include<ctime>
#include<stack> // I just prefer stack to QStack (for now awaawaawaawa
#include<queue> // prefer this
#include<random> //mt19937
#include<utility> //pair
#include<iostream>
#include<algorithm>
int mapn,mapm,mapbs;
std::mt19937 rd(time(0));
struct BFQ{
    int x,y,dir,frm;uint val;
    BFQ(int a,int b,int dr,int k){
        x=a;y=b;frm=k;dir=dr;val=rd();
    }
    bool operator<(const BFQ &t)const{
        return val<t.val;
    }
};
const uint LOOP_PRB=4252017623; // 1- x/4294967296
std::vector<std::vector<int> > mp;
std::vector<std::vector<int> > vis;
std::stack<std::pair<int,int> > dfss;
std::stack<std::pair<int,int> > dfstmp;
std::vector<std::pair<int,int> > pth;
std::priority_queue<BFQ> bfsq;
inline int Mabs(int x){return x>0?x:-x;}
const int axM[5]={0,1,0,-1,0};
const int ayM[5]={0,0,1,0,-1};
bool geningmz=false,fldn=false,fldm=false,flds=false;
void mazegen::genmz(int val){
    if(geningmz==true) return;
    mapn=mapm=mapbs=0; geningmz=true;
    QPalette pe; pe.setColor(QPalette::WindowText,val==1?Qt::red:Qt::magenta); ui->LWarn->setPalette(pe);
    QString infoS=val==1?"Error":"Warning";
    mapn=ui->In->text().toInt();   if(mapn<=0) { ui->LWarn->setText(infoS+" : \n    sorry, perhaps n isn\'t a legal integer.\n    note that legal means less than 1e7 and more than 0"); geningmz=false; return;}
    mapm=ui->Im->text().toInt();   if(mapm<=0) { ui->LWarn->setText(infoS+" : \n    sorry, perhaps m isn\'t a legal integer.\n    note that legal means less than 1e7 and more than 0"); geningmz=false; return;}
    mapbs=ui->Isz->text().toInt(); if(mapbs<=0){ ui->LWarn->setText(infoS+" : \n    sorry, perhaps sz isn\'t a legal integer.\n   note that legal means less than 1e7 and more than 0"); geningmz=false; return;}
    if((1ll*mapn*mapm*mapbs*mapbs>10000000ll)) { ui->LWarn->setText(infoS+" : \n    sorry, perhaps n*m*sz^2 is TOO BIG!!\n    you can try n=100,m=100,sz=5"); geningmz=false; return;}
    double pgd=ui->IM_Dd->text().toDouble(),pgr=ui->IM_Dr->text().toDouble(),pgu=ui->IM_Du->text().toDouble(),pgl=ui->IM_Dl->text().toDouble();
    if(pgd<=0) pgd=1e-9; if(pgr<=0) pgr=1e-9; if(pgu<=0) pgu=1e-9; if(pgl<=0) pgl=1e-9;
    std::stack<std::pair<int,int> >().swap(dfss);
    std::vector<std::pair<int,int> >().swap(pth);
    std::priority_queue<BFQ>().swap(bfsq);
    std::vector<std::vector<int> >().swap(mp);
    std::vector<int> tmp(mapm); mp.insert(mp.begin(),mapn,tmp); vis=mp;
    if(ui->comboBox->currentText()=="随机 dfs"){
        int x,y,dir;bool fd,fr,fu,fl;double choi,pg;
        dfss.push(std::make_pair(0,0));
        while(!dfss.empty()){
            x=dfss.top().first,y=dfss.top().second; dfss.pop();
            if(x+1==mapn&&y+1==mapm) break;
            vis[x][y]=1; pg=0;
            fd=(x+1==mapn||vis[x+1][y]==1);
            fr=(y+1==mapm||vis[x][y+1]==1);
            fu=(x==0||y==0||y+1==mapm||vis[x-1][y]==1);
            fl=(y==0||x==0||x+1==mapn||vis[x][y-1]==1);
            if(!fd) pg+=pgd; if(!fr) pg+=pgr;
            if(!fu) pg+=pgu; if(!fl) pg+=pgl;
            while(!dfstmp.empty()) dfstmp.pop();
            while(!(fd&&fr&&fu&&fl)){
                choi=rd()*1.0/4294967296.0;
                     if(fd==0&&choi<=(pgd/pg))                        { dfstmp.push(std::make_pair(x+1,y)); pg-=pgd; fd=1; mp[x+1][y]=3; }
                else if(fr==0&&choi<=(pgr/(pg-(fd?0:pgd))))           { dfstmp.push(std::make_pair(x,y+1)); pg-=pgr; fr=1; mp[x][y+1]=4; }
                else if(fu==0&&choi<=(pgu/(pg-(fd?0:pgd)-(fr?0:pgr)))){ dfstmp.push(std::make_pair(x-1,y)); pg-=pgu; fu=1; mp[x-1][y]=1; }
                else if(fl==0)                                        { dfstmp.push(std::make_pair(x,y-1)); pg-=pgl; fl=1; mp[x][y-1]=2; }
            }
            while(!dfstmp.empty()){dfss.push(dfstmp.top());dfstmp.pop();}
        }
        x=mapn-1; y=mapm-1; pth.push_back(std::make_pair(x,y));
        while(x!=0||y!=0){
            dir=mp[x][y]; x+=axM[dir]; y+=ayM[dir];
            pth.push_back(std::make_pair(x,y));
        }
        std::reverse(pth.begin(),pth.end());
        std::vector<std::vector<int> >().swap(mp); mp.insert(mp.begin(),mapn,tmp); vis=mp;
        std::pair<int,int> lsp; int tot=0;
        for(auto p:pth){
            if(p.first!=0||p.second!=0){
                     if(lsp.first==p.first-1&&lsp.second==p.second){mp[lsp.first][lsp.second]|=1;mp[p.first][p.second]|=4;}
                else if(lsp.first==p.first&&lsp.second==p.second-1){mp[lsp.first][lsp.second]|=2;mp[p.first][p.second]|=8;}
                else if(lsp.first==p.first+1&&lsp.second==p.second){mp[lsp.first][lsp.second]|=4;mp[p.first][p.second]|=1;}
                else if(lsp.first==p.first&&lsp.second==p.second+1){mp[lsp.first][lsp.second]|=8;mp[p.first][p.second]|=2;}
            }
            lsp=p; vis[p.first][p.second]=++tot;
        }
        for(auto p:pth){
            if( p.first+1 <mapn && vis[p.first+1][p.second]==0 ) bfsq.push(BFQ(p.first+1,p.second,1,++tot));
            if( p.second+1<mapm && vis[p.first][p.second+1]==0 ) bfsq.push(BFQ(p.first,p.second+1,2,++tot));
            if( p.first   >0    && vis[p.first-1][p.second]==0 ) bfsq.push(BFQ(p.first-1,p.second,3,++tot));
            if( p.second  >0    && vis[p.first][p.second-1]==0 ) bfsq.push(BFQ(p.first,p.second-1,4,++tot));
        }
        for(BFQ u=BFQ(0,0,0,0);!bfsq.empty();){
            u=bfsq.top();bfsq.pop(); if(vis[u.x][u.y]) continue;
            vis[u.x][u.y]=u.frm; mp[u.x][u.y]|=1<<((u.dir-1)^2);
            mp[u.x-axM[u.dir]][u.y-ayM[u.dir]]|=1<<(u.dir-1);
            if( u.x+1<mapn && vis[u.x+1][u.y]==0 ) bfsq.push(BFQ(u.x+1,u.y,1,u.frm));
            if( u.y+1<mapm && vis[u.x][u.y+1]==0 ) bfsq.push(BFQ(u.x,u.y+1,2,u.frm));
            if(   u.x>0    && vis[u.x-1][u.y]==0 ) bfsq.push(BFQ(u.x-1,u.y,3,u.frm));
            if(   u.y>0    && vis[u.x][u.y-1]==0 ) bfsq.push(BFQ(u.x,u.y-1,4,u.frm));
            if( u.x+1<mapn && vis[u.x+1][u.y]==u.frm && rd()>=LOOP_PRB ) mp[u.x][u.y]|=1, mp[u.x+1][u.y]|=4;
            if( u.y+1<mapm && vis[u.x][u.y+1]==u.frm && rd()>=LOOP_PRB ) mp[u.x][u.y]|=2, mp[u.x][u.y+1]|=8;
            if(   u.x>0    && vis[u.x-1][u.y]==u.frm && rd()>=LOOP_PRB ) mp[u.x][u.y]|=4, mp[u.x-1][u.y]|=1;
            if(   u.y>0    && vis[u.x][u.y-1]==u.frm && rd()>=LOOP_PRB ) mp[u.x][u.y]|=8, mp[u.x][u.y-1]|=2;
        }
        int curc=0;
        QImage img(mapbs*(mapn*2+1),mapbs*(mapm*2+1),QImage::Format_RGB32);
        img.fill(0xff000000);
        for(int i=0;i<mapn;i++){
            for(int j=0;j<mapm;j++){
                for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                    img.setPixel((i*2+1)*mapbs+ii,(j*2+1)*mapbs+jj,QRgb(0xffffffff));
                if(mp[i][j]&1) for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                    img.setPixel((i*2+2)*mapbs+ii,(j*2+1)*mapbs+jj,QRgb(0xffffffff));
                if(mp[i][j]&2) for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                    img.setPixel((i*2+1)*mapbs+ii,(j*2+2)*mapbs+jj,QRgb(0xffffffff));
                if(mp[i][j]&4) for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                    img.setPixel((i*2+0)*mapbs+ii,(j*2+1)*mapbs+jj,QRgb(0xffffffff));
                if(mp[i][j]&8) for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                    img.setPixel((i*2+1)*mapbs+ii,(j*2+0)*mapbs+jj,QRgb(0xffffffff));
            }
        }
        pork=img;
        lsp=std::make_pair(0,0);
        for(auto p:pth){
            for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                img.setPixel((p.first*2+1)*mapbs+ii,(p.second*2+1)*mapbs+jj,QRgb(0xff6060ff));
            for(int ii=0;ii<mapbs;ii++) for(int jj=0;jj<mapbs;jj++)
                img.setPixel((p.first+lsp.first+1)*mapbs+ii,(p.second+lsp.second+1)*mapbs+jj,QRgb(0xff6060ff));
            lsp=p;
        }
        beef=img;
        img=img.scaled(ui->ptpi->width(),ui->ptpi->height(),Qt::KeepAspectRatio);
        ui->ptpi->setPixmap(QPixmap::fromImage(img));
    }
    geningmz=false;
}
void mazegen::on_Bstart_clicked(){
    genmz(1); //1 for error
}
void mazegen::on_Isz_editingFinished(){
    flds=1; if(fldn&&fldm&&flds) genmz(0);
}
void mazegen::on_In_editingFinished(){
    fldn=1; if(fldn&&fldm&&flds) genmz(0);
}
void mazegen::on_Im_editingFinished(){
    fldm=1; if(fldn&&fldm&&flds) genmz(0);
}
void mazegen::on_BTview_clicked(){
    result *nwin=new result(pork,beef); nwin->show();
}
#include<QFileDialog>
void mazegen::saveAction(QImage img){
    QString fileName=QFileDialog::getSaveFileName(this,"保存",QCoreApplication::applicationFilePath(),tr("Lossless compression (*.png *.bpm);;Lossy compression (*.jpg *.jpeg);;Images (*.png *.bpm *.jpg *.jpeg)"));
    if(fileName.isEmpty()) return;
    img.save(fileName);
}
void mazegen::on_BTsav_clicked(){
    saveAction(pork);
}
void mazegen::on_BTsvans_clicked(){
    saveAction(beef);
}
#include<QKeyEvent>
void mazegen::keyPressEvent(QKeyEvent *k){
    if(k->modifiers()==Qt::ControlModifier && k->key()==Qt::Key_S){
        saveAction(beef);
    }
}
