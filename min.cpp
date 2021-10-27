#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define S struct
#define O operator
#define H return
typedef float f;typedef int i;S v{f x,y,z;v(){}v(f a,f b,f c){x=a;y=b;z=c;}v O*(f d){H v(d*x,d*y,d*z);}v O+(v e)
{H v(e.x+x,e.y+y,e.z+z);}f O%(v e){H e.x*x+e.y*y+e.z*z;}v O^(v e){H v(e.z*y-e.y*z,e.x*z-e.z*x,e.y*x-e.x*y);}v O!
(){H *this*(1/sqrt(*this%*this));}};i G[]={133232,133256,69892,127236,69636,40964,40964,16388,0};f R(){H (f)rand
()/RAND_MAX;}i t(v s,v e,v &n,f &d){d=1e9;i h=0;f m=-s.z/e.z;if(.01<m){d=m;n=v(0,0,1);h=1;}for(i k=19;k--;)for(i 
j=9;j--;)if(G[j]&1<<k){v w=s+v(-k,0,-j-4);f b=w%e;f c=w%w-1;f q=b*b-c;if(q>0){f s=-b-sqrt(q);if(s<d&&s>.01)
{d=s;n=!(w+e*d);h=2;}}}H h;}v a(v s,v e){f d;v n;i m=t(s,e,n,d);if(!m){f g=pow(1-e.z,8);H v(g*.53,g*.81,pow(1-
e.z,2)*.92);}v I=s+e*d;v D=!(v(9+R(),9+R(),16)+I*-1);v V=e+n*(n%e*-2);f L=D%n;if(L<0||t(I,D,n,d)){L=0;}f C=pow(D
%V*(L>0),99);if(m&1){I=I*.2;H ((i)(ceil(I.x)+ceil(I.y))&1?v(2,2,2):v(1,1,1))*(L*.2+.1);}H v(C,C,C)+a(I,V)*.5;}i 
main(){v F=!(v(-6,-16,0));v U=!(v(0,0,1)^F)*.002;v M=!(F^U)*.002,c=(U+M)*-256+F;printf("P6 512 512 255 ");for(i 
y=512;y--;)for(i x=512;x--;){v C(13,13,13);for(i N=64;N--;){v T=U*(R()-.5)*99+M*(R()-.5)*99;C=a(v(17,16,8)+T,!
(T*-1+(U*(R()+x)+M*(y+R())+c)*16))*3.5+C;}printf("%c%c%c",(i)C.x,(i)C.y,(i)C.z);}}