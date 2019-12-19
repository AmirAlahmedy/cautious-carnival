#include "headers.h"
#include "Queue.h"
#include "priority_queue.h"
bool A256[4]={0,0,0,0};
bool A128[8]={0,0,0,0,0,0,0,0};
bool A64[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A32[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A16[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A8[128]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A4[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A2[512]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool A1[1024]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void Allocate(struct process *p)
{
    FILE* fp;
    if(p->memsize>128 && p->memsize<=256)
    {printf("inside function");
        for(int i=0;i<4;i++)
            {
                if(A256[i]==0)
                {
                    
                    A256[i]=1;
                    p->index=i;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*256, (i*256)+255);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A128[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A64[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A32[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A16[(i*16)+j]=1;}
                    for(int j=0;j<32;j++)
                    {A8[(i*32)+j]=1;}
                    for(int j=0;j<64;j++)
                    {A4[(i*64)+j]=1;}
                    for(int j=0;j<128;j++)
                    {A2[(i*128)+j]=1;}
                    for(int j=0;j<256;j++)
                    {A1[(i*256)+j]=1;}
                    return;
                }
            }
    }
    else if(p->memsize>64 && p->memsize<=128)
    {
        ///////////////////////////////////////////////////////////////////
        for(int i=0;i<8;i++)
        {
            if(A128[i]==0&&A256[i/2]==1)//to make sure that I divide only if necessary
            {
                A128[i]=1;
                p->index=i;
                //A256[i/2]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*128, (i*128)+127);
                fclose(fp);
                for(int j=0;j<2;j++)
                    {A64[(i*2)+j]=1;}
                for(int j=0;j<4;j++)
                    {A32[(i*4)+j]=1;}
                for(int j=0;j<8;j++)
                    {A16[(i*8)+j]=1;}
                for(int j=0;j<16;j++)
                    {A8[(i*16)+j]=1;}
                for(int j=0;j<32;j++)
                    {A4[(i*32)+j]=1;}
                for(int j=0;j<64;j++)
                    {A2[(i*64)+j]=1;}
                for(int j=0;j<128;j++)
                    {A1[(i*128)+j]=1;}
                    return;
            }
        }
        ///////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<8;i++)
        {
            if(A128[i]==0&&A256[i/2]==0)
            {
                A128[i]=1;
                p->index=i;
                A256[i/2]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*128, (i*128)+127);
                fclose(fp);
                for(int j=0;j<2;j++)
                    {A64[(i*2)+j]=1;}
                for(int j=0;j<4;j++)
                    {A32[(i*4)+j]=1;}
                for(int j=0;j<8;j++)
                    {A16[(i*8)+j]=1;}
                for(int j=0;j<16;j++)
                    {A8[(i*16)+j]=1;}
                for(int j=0;j<32;j++)
                    {A4[(i*32)+j]=1;}
                for(int j=0;j<64;j++)
                    {A2[(i*64)+j]=1;}
                for(int j=0;j<128;j++)
                    {A1[(i*128)+j]=1;}
                    return;
            }
        }
        
    }
    else if(p->memsize>32 && p->memsize<=64)
    {
        for(int i=0;i<16;i++)
        {
            if(A64[i]==0&&A128[i/2]==1)//to make sure that I divide only if necessary
            {
                A64[i]=1;
                //A128[i/2]=1;
                A256[i/4]=1;
                p->index=i;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*64, (i*64)+63);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A32[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A16[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A8[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A4[(i*16)+j]=1;}
                    for(int j=0;j<32;j++)
                    {A2[(i*32)+j]=1;}
                    for(int j=0;j<64;j++)
                    {A1[(i*64)+j]=1;}
                    return;
            }
        }
        /////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
         for(int i=0;i<16;i++)
        {
            if(A64[i]==0&&A128[i/2]==0)
            {
                A64[i]=1;
                A128[i/2]=1;
                A256[i/4]=1;
                p->index=i;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*64, (i*64)+63);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A32[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A16[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A8[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A4[(i*16)+j]=1;}
                    for(int j=0;j<32;j++)
                    {A2[(i*32)+j]=1;}
                    for(int j=0;j<64;j++)
                    {A1[(i*64)+j]=1;}
                    return;
            }
        }
    }
    else if(p->memsize>16 && p->memsize<=32)
    {
        for(int i=0;i<32;i++)
        {
            if(A32[i]==0&&A64[i/2]==1)//to make sure that I divide only if necessary
            {
                A32[i]=1;
                p->index=i;
                //A64[i/2]=1;
                A128[i/4]=1;
                A256[i/8]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*32, (i*32)+31);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A16[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A8[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A4[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A2[(i*16)+j]=1;}
                    for(int j=0;j<32;j++)
                    {A1[(i*32)+j]=1;}
                    return;
            }
        }  
        ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<32;i++)
        {
            if(A32[i]==0&&A64[i/2]==0)
            {
                A32[i]=1;
                p->index=i;
                A64[i/2]=1;
                A128[i/4]=1;
                A256[i/8]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*32, (i*32)+31);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A16[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A8[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A4[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A2[(i*16)+j]=1;}
                    for(int j=0;j<32;j++)
                    {A1[(i*32)+j]=1;}
                    return;
            }
        }  
    }
    else if(p->memsize>8 && p->memsize<=16)
    {
        for(int i=0;i<64;i++)
        {
            if(A16[i]==0&&A32[i/2]==1)//to make sure that I divide only if necessary
            {
                A16[i]=1;
                p->index=i;
               // A32[i/2]=1;
                A64[i/4]=1;
                A128[i/8]=1;
                A256[i/16]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*16, (i*16)+15);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A8[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A4[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A2[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A1[(i*16)+j]=1;}
                    return;
            }
        }  
        ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<64;i++)
        {
            if(A16[i]==0&&A32[i/2]==0)
            {
                A16[i]=1;
                p->index=i;
                A32[i/2]=1;
                A64[i/4]=1;
                A128[i/8]=1;
                A256[i/16]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*16, (i*16)+15);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A8[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A4[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A2[(i*8)+j]=1;}
                    for(int j=0;j<16;j++)
                    {A1[(i*16)+j]=1;}
                    return;
            }
        }  
    }
    else if(p->memsize>4 && p->memsize<=8)
    {
        for(int i=0;i<128;i++)
        {
            if(A8[i]==0&&A16[i/2]==1)//to make sure that I divide only if necessary
            {
                A8[i]=1;
                p->index=i;
                //A16[i/2]=1;
                A32[i/4]=1;
                A64[i/8]=1;
                A128[i/16]=1;
                A256[i/32]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*8, (i*8)+7);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A4[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A2[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A1[(i*8)+j]=1;}
                    return;
            }
        }  
        ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<128;i++)
        {
            if(A8[i]==0&&A16[i/2]==0)
            {
                A8[i]=1;
                p->index=i;
                A16[i/2]=1;
                A32[i/4]=1;
                A64[i/8]=1;
                A128[i/16]=1;
                A256[i/32]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*8, (i*8)+7);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A4[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A2[(i*4)+j]=1;}
                    for(int j=0;j<8;j++)
                    {A1[(i*8)+j]=1;}
                    return;
            }
        }  
    }
     else if(p->memsize>2 && p->memsize<=4)
    {
        for(int i=0;i<256;i++)
        {
            if(A4[i]==0&&A8[i/2]==1)//to make sure that I divide only if necessary
            {
                A4[i]=1;
                p->index=i;
                //A8[i/2]=1;
                A16[i/4]=1;
                A32[i/8]=1;
                A64[i/16]=1;
                A128[i/32]=1;
                A256[i/64]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*4, (i*4)+3);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A2[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A1[(i*4)+j]=1;}
                    return;
            }
        }  
        ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<256;i++)
        {
            if(A4[i]==0&&A8[i/2]==0)
            {
                A4[i]=1;
                p->index=i;
                A8[i/2]=1;
                A16[i/4]=1;
                A32[i/8]=1;
                A64[i/16]=1;
                A128[i/32]=1;
                A256[i/64]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*4, (i*4)+3);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A2[(i*2)+j]=1;}
                    for(int j=0;j<4;j++)
                    {A1[(i*4)+j]=1;}
                    return;
            }
        }  
    }
    else if(p->memsize>1 && p->memsize<=2)
    {
        for(int i=0;i<512;i++)
        {
            if(A2[i]==0&&A4[i/2]==1)//to make sure that I divide only if necessary
            {
                A2[i]=1;
                p->index=i;
                //A4[i/2]=1;
                A8[i/4]=1;
                A16[i/8]=1;
                A32[i/16]=1;
                A64[i/32]=1;
                A128[i/64]=1;
                A256[i/128]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*2, (i*2)+1);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A1[(i*2)+j]=1;}
                    return;
            }
        }  
        ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
        for(int i=0;i<512;i++)
        {
            if(A2[i]==0&&A4[i/2]==0)
            {
                A2[i]=1;
                p->index=i;
                A4[i/2]=1;
                A8[i/4]=1;
                A16[i/8]=1;
                A32[i/16]=1;
                A64[i/32]=1;
                A128[i/64]=1;
                A256[i/128]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*2, (i*2)+1);
                fclose(fp);
                    for(int j=0;j<2;j++)
                    {A1[(i*2)+j]=1;}
                    return;
            }
        }  
    }
      else if(p->memsize>0 && p->memsize<=1)
    {
        for(int i=0;i<1024;i++)
        {
            if(A1[i]==0&&A2[i/2]==1)//to make sure that I divide only if necessary
            {
                A1[i]=1;
                p->index=i;
                //A2[i/2]=1;
                A4[i/4]=1;
                A8[i/8]=1;
                A16[i/16]=1;
                A32[i/32]=1;
                A64[i/64]=1;
                A128[i/128]=1;
                A256[i/256]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*1, (i*1)+0);
                fclose(fp);
                return;
            }
        }  
         ///////////////////////////////////////////////////////////////////////
        //-------------------------We have to partition-------------------------
         for(int i=0;i<1024;i++)
        {
            if(A1[i]==0&&A2[i/2]==0)//to make sure that I divide only if necessary
            {
                A1[i]=1;
                p->index=i;
                A2[i/2]=1;
                A4[i/4]=1;
                A8[i/8]=1;
                A16[i/16]=1;
                A32[i/32]=1;
                A64[i/64]=1;
                A128[i/128]=1;
                A256[i/256]=1;
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tallocated\t%d\tbytes\tfor\tprocess\t%d\tfrom\t%d\tto\t%d\n", p->arrival, p->memsize, p->id, i*1, (i*1)+0);
                fclose(fp);
                return;
            }
        }  
    }
}
void Deallocate(struct process* p,int finish)
{
    int i=0;FILE* fp;
   if(p->memsize>128 && p->memsize<=256)
    {
                    i=p->index;
                    A256[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*256, (i*256)+255);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A128[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A64[(i*4)+j]=0;}
                    for(int j=0;j<8;j++)
                    {A32[(i*8)+j]=0;}
                    for(int j=0;j<16;j++)
                    {A16[(i*16)+j]=0;}
                    for(int j=0;j<32;j++)
                    {A8[(i*32)+j]=0;}
                    for(int j=0;j<64;j++)
                    {A4[(i*64)+j]=0;}
                    for(int j=0;j<128;j++)
                    {A2[(i*128)+j]=0;}
                    for(int j=0;j<256;j++)
                    {A1[(i*256)+j]=0;}
                    return;
            
    }
    else if(p->memsize>64 && p->memsize<=128)
    {
                i=p->index;
                A128[i]=0;
                if(i%2==0)//even multiple
                {
                    if(A128[i+1]==0)
                    {
                        A256[i/2]=0;
                    }
                }
                else if(i%2==1)//odd multiple
                {
                    if(A128[i-1]==0)
                    {
                        A256[i/2]=0;
                    }
                }
                fp = fopen("Memory.log", "a");
                fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*128, (i*128)+127);
                fclose(fp);
                for(int j=0;j<2;j++)
                    {A64[(i*2)+j]=0;}
                for(int j=0;j<4;j++)
                    {A32[(i*4)+j]=0;}
                for(int j=0;j<8;j++)
                    {A16[(i*8)+j]=0;}
                for(int j=0;j<16;j++)
                    {A8[(i*16)+j]=0;}
                for(int j=0;j<32;j++)
                    {A4[(i*32)+j]=0;}
                for(int j=0;j<64;j++)
                    {A2[(i*64)+j]=0;}
                for(int j=0;j<128;j++)
                    {A1[(i*128)+j]=0;}
                    return;
    }
    else if(p->memsize>32 && p->memsize<=64)
    {
                    i=p->index;
                    A64[i]=0;
                    if(i%2==0)//even multiple
                    {
                        if(A64[i+1]==0)
                        {
                            A128[i/2]=0;
                            if((i/2)%2==0)
                            {
                                if(A128[(i/2)+1]==0)
                                {
                                    A256[i/4]=0;
                                }
                            }
                            else if((i/2)%2==1)
                            {
                                if(A128[(i/2)-1]==0)
                                {
                                    A256[i/4]=0;
                                }
                            }
                        }
                    }
                    else if(i%2==1)//odd multiple
                    {
                        if(A64[i-1]==0)
                        {
                            A128[i/2]=0;
                            if((i/2)%2==0)
                            {
                                if(A128[(i/2)+1]==0)
                                {
                                    A256[i/4]=0;
                                }
                            }
                            else if((i/2)%2==1)
                            {
                                if(A128[(i/2)-1]==0)
                                {
                                    A256[i/4]=0;
                                }
                            }
                        }
                    }
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*64, (i*64)+63);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A32[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A16[(i*4)+j]=0;}
                    for(int j=0;j<8;j++)
                    {A8[(i*8)+j]=0;}
                    for(int j=0;j<16;j++)
                    {A4[(i*16)+j]=0;}
                    for(int j=0;j<32;j++)
                    {A2[(i*32)+j]=0;}
                    for(int j=0;j<64;j++)
                    {A1[(i*64)+j]=0;}
                    return;
    }
    else if(p->memsize>16 && p->memsize<=32)
    {

                    i=p->index;
                    A32[i]=0;
                    if(i%2==0)
                    {
                        if(A32[i+1]==0)
                        {
                            A64[i/2]=0;
                            if((i/2)%2==0)
                            {
                                if(A64[(i/2)+1]==0)
                                {
                                    A128[i/4]=0;
                                    if((i/4)%2==0)
                                    {
                                        if(A128[(i/4)+1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                    else if((i/4)%2==1)
                                    {
                                        if(A128[(i/4)-1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                }
                            }
                            else if((i/2)%2==1)
                            {
                                if(A64[(i/2)-1]==0)
                                {
                                    A128[i/4]=0;
                                    if((i/4)%2==0)
                                    {
                                        if(A128[(i/4)+1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                    else if((i/4)%2==1)
                                    {
                                        if(A128[(i/4)-1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if(i%2==1)
                    {
                        if(A32[i-1]==0)
                        {
                            A64[i/2]=0;
                            if((i/2)%2==0)
                            {
                                if(A64[(i/2)+1]==0)
                                {
                                    A128[i/4]=0;
                                    if((i/4)%2==0)
                                    {
                                        if(A128[(i/4)+1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                    else if((i/4)%2==1)
                                    {
                                        if(A128[(i/4)-1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                }
                            }
                            else if((i/2)%2==1)
                            {
                                if(A64[(i/2)-1]==0)
                                {
                                    A128[i/4]=0;
                                    if((i/4)%2==0)
                                    {
                                        if(A128[(i/4)+1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                    else if((i/4)%2==1)
                                    {
                                        if(A128[(i/4)-1]==0)
                                        {
                                            A256[(i/8)]=0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*32, (i*32)+31);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A16[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A8[(i*4)+j]=0;}
                    for(int j=0;j<8;j++)
                    {A4[(i*8)+j]=0;}
                    for(int j=0;j<16;j++)
                    {A2[(i*16)+j]=0;}
                    for(int j=0;j<32;j++)
                    {A1[(i*32)+j]=0;}
                    return;
    }
    else if(p->memsize>8 && p->memsize<=16)
    {
                    i=p->index;
                    A16[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*16, (i*16)+15);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A8[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A4[(i*4)+j]=0;}
                    for(int j=0;j<8;j++)
                    {A2[(i*8)+j]=0;}
                    for(int j=0;j<16;j++)
                    {A1[(i*16)+j]=0;}
                    return;
    }
    else if(p->memsize>4 && p->memsize<=8)
    {
                    i=p->index;
                    A8[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*8, (i*8)+7);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A4[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A2[(i*4)+j]=0;}
                    for(int j=0;j<8;j++)
                    {A1[(i*8)+j]=0;}
                    return;
    }
     else if(p->memsize>2 && p->memsize<=4)
    {
                    i=p->index;
                    A4[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*4, (i*4)+3);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A2[(i*2)+j]=0;}
                    for(int j=0;j<4;j++)
                    {A1[(i*4)+j]=0;}
                    return;
    }
      else if(p->memsize>1 && p->memsize<=2)
    {
                    i=p->index;
                    A2[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*2, (i*2)+1);
                    fclose(fp);
                    for(int j=0;j<2;j++)
                    {A1[(i*2)+j]=1;}
                    return; 
    }
      else if(p->memsize>0 && p->memsize<=1)
    {
                    i=p->index;
                    A1[i]=0;
                    fp = fopen("Memory.log", "a");
                    fprintf(fp, "#At time\t%d\tfreed\t%d\tbytes\tfrom\tprocess\t%d\tfrom\t%d\tto\t%d\n", finish, p->memsize, p->id, i*1, (i*1)+0);
                    fclose(fp);
                    return;
    }
}

int *allSent;

/**
 * The type sig_atomic_t is used in C99 to guarantee
 * that a variable can be accessed/modified in an atomic way
 * in the case an interruption (reception of a signal for example) happens.
 */
static volatile sig_atomic_t done_waiting = 0;

static void sigusr_handler(int signum)
{
    if (signum == SIGCONT)
    {
        printf("Signal caught, a process is being receeived\n");
        done_waiting = 1;
    }
    else if (signum == SIGUSR2)
    {
        printf("Signal caught, Child terminated\n");
        done_waiting = 1;
    }
}

void my_pause()
{
    /**
   *  In ISO C, the signal system call is used
   *  to call a specific handler when a specified
   *  signal is received by the current process.
   *  In POSIX.1, it is encouraged to use the sigaction APIs.
   **/
    signal(SIGUSR2, sigusr_handler);
    signal(SIGCONT, sigusr_handler);
    done_waiting = 0;
    while (!done_waiting)
    {
        sleep(INT_MAX);
    }
}

float Average(float data[], int n)
{
    float sum = 0.0, mean, SD = 0.0;
    for (int i = 0; i < n; ++i)
    {
        sum += data[i];
    }
    mean = sum / n;
    return mean;
}

float STD(float data[], int n)
{
    float mean, SD = 0.0;
    int i;

    mean = Average(data, n);

    for (i = 0; i < n; ++i)
        SD += pow(data[i] - mean, 2);
    return sqrt(SD / n);
}

void sigalarm_handler(int signum)
{
    printf("alarm fired at t=%ld\n", time(NULL)); // write a message when called
}

int num = 0, pid[MAXCHAR], CPUutil = 0, firstArr = 0;
float AWTA = 0.0, AW = 0.0, SD = 0.0, WTA[MAXCHAR], W[MAXCHAR], TRT = 0;
struct process temp, discarded;
void roundRobin(struct Queue *Q, key_t msgqid, FILE *fp, int Quantum)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;
    alarm(1);
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);
    if (p_rec.state == ARRIVED)
    {
        num++;
        if(num == 1)
            firstArr = p_rec.arrival;
        printf("num: %d\n", num);
        enQueue(Q, p_rec);
    }
    if (temp.id != 0)
        enQueue(Q, temp);

    if (!isEmpty(Q))
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: temp is %ld %d %d %d\n", getClk(), temp.id, temp.arrival, temp.runtime, temp.priority);

        printf("at %d: front is  %ld %d %d %d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.priority);

        if (Q->front->next != NULL)
            printf("at %d: front next is  %ld %d %d %d\n", getClk(), Q->front->next->key.id, Q->front->next->key.arrival, Q->front->next->key.runtime, Q->front->next->key.priority);

        printf("at %d: rear is %ld %d %d %d\n", getClk(), Q->rear->key.id, Q->rear->key.arrival, Q->rear->key.runtime, Q->rear->key.priority);

        pid[num] = fork();
        if (pid[num] == 0)
        {
            Q->front->key.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", Q->front->key.runtime);
            system(line);
            exit(7);
        }

        if (Q->front->key.state == ARRIVED)
        {
            Q->front->key.ST = getClk();
            Q->front->key.wait = Q->front->key.ST - Q->front->key.arrival;
            Q->front->key.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n", pid[num - 1], pid[num]);

        kill(Q->front->key.pid, SIGCONT);
        if (Q->front->key.state == STOPPED)
        {
            Q->front->key.state = RESUMED;
            Q->front->key.wait = getClk() - ((Q->front->key.runtime - Q->front->key.remain) + Q->front->key.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
            fclose(fp);
        }

        if (Q->front->key.remain <= Quantum)
        {
            ch_pid = wait(&stat_loc);
            if (!(stat_loc & 0x00FF))
            {
                printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
                Q->front->key.remain = 0;
            }
        }
        else
        {
            alarm(Quantum);
            sleep(INT_MAX);
            kill(pid[num], SIGSTOP);
            Q->front->key.remain -= Quantum;
        }

        if (Q->front->key.state == RESUMED || Q->front->key.state == STARTED)
        {
            if (Q->front->key.remain == 0)
            {
                Q->front->key.state = FINISHED;
                int TA = getClk() - Q->front->key.ST;
                Q->front->key.wait = TA - Q->front->key.runtime;
                W[Q->front->key.id] = Q->front->key.wait;

                if (Q->front->key.runtime != 0)
                    WTA[Q->front->key.id] = TA / Q->front->key.runtime;
                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait, TA, WTA[Q->front->key.id]);
                fclose(fp);

                // calculting Total runtime and CPU util
                TRT += Q->front->key.runtime;
                CPUutil = (TRT / (getClk() - firstArr)) * 100;

                // calculating Average WTA and Average waiting time
                AWTA = Average(WTA, num);
                AW = Average(W, num);

                // calculating the standard deviation of the WTA
                SD = STD(WTA, num);

                // printing into scheduler.perf
                FILE *ftp = fopen("scheduler.perf", "w");
                fprintf(ftp, "CPU utilization = %d%%\nAvg WTA = %.2f\nAvg Waiting = %.2f\nStd WTA = %.2f", CPUutil, AWTA, AW, SD);
                fclose(ftp);
            }
            else
            {
                Q->front->key.state = STOPPED;
                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), Q->front->key.id, Q->front->key.arrival, Q->front->key.runtime, Q->front->key.remain, Q->front->key.wait);
                fclose(fp);
            }
        }

        if (Q->front->key.remain == 0)
        {
            discarded = (deQueue(Q))->key;
            temp.id = 0;
        }
        else
        {
            temp = Q->front->key;
            discarded = (deQueue(Q))->key;
        }
    }
}
/* used in HPF and SRTN */
int len, num_finished = 0;
Node *PQ;
bool noProcRunning = 1;
struct process running;
void HPF(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;

    // my_pause();
    int rec_op = *allSent ? IPC_NOWAIT : !IPC_NOWAIT;
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, rec_op);
    if (p_rec.state == ARRIVED)
    {
        Allocate(&p_rec);

        num++;
        push(&PQ, p_rec, p_rec.priority);
        len++;
        if(num == 1){
           running = peek(&PQ);
            puts("before");
            pop(&PQ);
            len--;
            firstArr = p_rec.arrival;
        }
        printf("peek is %ld\n", peek(&PQ).id);
        
        printf("num: %d, len: %d\n", num, len);
    }

    printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
    printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
    printf("at %d: running is %ld %d %d %d\n", getClk(), running.id, running.arrival,running.runtime, running.priority);
    
    if (running.id != 0)
    {
            if(noProcRunning)
            {
                printf("memsize is %d\n", running.memsize);
                // Allocate(&running);
                // printf("After allocate function %d\n",running.index);
                noProcRunning = false;
                pid[num] = fork();
                if (pid[num] == 0)
                {
                    running.pid = pid[num];
                    char line[20];
                    sprintf(line, "./process.out %d", running.runtime);
                    system(line);
                    kill(getppid(), SIGUSR2);
                    exit(7);
                }
            if (running.state == ARRIVED)
            {
                running.ST = getClk();
                running.wait = running.ST - running.arrival;
                running.state = STARTED;
                fp = fopen("scheduler.log", "a");
                fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), running.id, running.arrival, running.runtime, running.remain, running.wait);
                fclose(fp);
            }
            my_pause();
        }

        printf("prev pid: %d, curr pid: %d\n\n", pid[num - 1], pid[num]);

        
        ch_pid = waitpid(-1, &stat_loc, 0 | WNOHANG);
        if (ch_pid != 0/* WIFEXITED(stat_loc) */ && !(stat_loc & 0x00FF))
        {
            num_finished++;
            Deallocate(&running, getClk());
            noProcRunning = true;
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            running.remain = 0;

            running.state = FINISHED;
            int TA = getClk() - running.ST;
            running.wait = TA - running.runtime;
            W[running.id] = running.wait;

            if (running.runtime != 0)
                WTA[running.id] = TA / running.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), running.id, running.arrival, running.runtime, running.remain, running.wait, TA, WTA[running.id]);
            fclose(fp);
            printf("at %d: process popped is %ld %d %d %d\n\n", getClk(), running.id, running.arrival, running.runtime, running.priority);
            if(len)
            {
                running = peek(&PQ);
                pop(&PQ);
                len--;
            }

            // calculting Total runtime and CPU util
            TRT += running.runtime;
            CPUutil = (TRT / ((getClk() - firstArr))) * 100;

            // calculating Average WTA and Average waiting time
            AWTA = Average(WTA, num);
            AW = Average(W, num);

            // calculating the standard deviation of the WTA
             SD = STD(WTA, num);

            //printing into scheduler.perf
            fp = fopen("scheduler.perf", "w");
            fprintf(fp, "CPU utilization = %d%%\nAvg WTA = %.2f\nAvg Waiting = %.2f\nStd WTA = %.2f", CPUutil, AWTA, AW, SD);
            fclose(fp);
        }
    }
    printf("number of finished processes is %d\n", num_finished);
    if (num != 0 && num == num_finished)
        sleep(INT_MAX);
}
void SJF(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;

    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, !IPC_NOWAIT);

    if (p_rec.state == ARRIVED)
    {
        num++;
        push(&PQ, p_rec, p_rec.remain);
        printf("peek is %ld\n", peek(&PQ).id);
        len++;
        printf("num: %d, len: %d\n", num, len);
    }

    if (len)
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);

        if (PQ->next->data.state == RESUMED || PQ->next->data.state == STARTED)
        {
            kill(pid[num - 1], SIGSTOP); // stop the running process
            if (PQ->next->data.state = STARTED)
                PQ->next->data.remain = PQ->next->data.runtime - (getClk() - PQ->next->data.ST);
            // else if(PQ->data.state = RESUMED)
            //     PQ->data.remain =
            PQ->next->data.state = STOPPED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.remain, PQ->next->data.wait);
            fclose(fp);
        }

        pid[num] = fork();
        if (pid[num] == 0)
        {
            PQ->data.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", PQ->data.runtime);
            system(line);
            exit(7);
        }

        if (PQ->data.state == ARRIVED)
        {
            PQ->data.ST = getClk();
            PQ->data.wait = PQ->data.ST - PQ->data.arrival;
            PQ->data.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n\n", pid[num - 1], pid[num]);

        if (PQ->data.state == STOPPED)
        {
            kill(PQ->data.pid, SIGCONT);
            PQ->data.state = RESUMED;
            PQ->data.wait = getClk() - ((PQ->data.runtime - PQ->data.remain) + PQ->data.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        // alarm(5);
        ch_pid = waitpid(PQ->data.pid, &stat_loc, 0);
        if (ch_pid != 0 && !(stat_loc & 0x00FF))
        {
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            PQ->data.remain = 0;

            PQ->data.state = FINISHED;
            int TA = getClk() - PQ->data.ST;
            PQ->data.wait = TA - PQ->data.runtime;
            float WTA = 0;
            if (PQ->data.runtime != 0)
                WTA = TA / PQ->data.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait, TA, WTA);
            fclose(fp);
            printf("at %d: process popped is %ld %d %d %d\n\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
            pop(&PQ);
            len--;
        }
    }
}

void SRTN(key_t msgqid, FILE *fp)
{
    struct process p_rec = {.state = UNDEFINED};
    int ch_pid, stat_loc;

    // if (!(*allSent))
    // int rcvop = *allSent ? !IPC_NOWAIT : IPC_NOWAIT;
    my_pause();
    msgrcv(msgqid, &p_rec, sizeof(p_rec), 0, IPC_NOWAIT);

    if (p_rec.state == ARRIVED)
    {
        num++;
        push(&PQ, p_rec, p_rec.remain);
        printf("peek is %ld\n", peek(&PQ).id);
        if (num == 1)
            firstArr = p_rec.arrival;
        len++;
        printf("num: %d, len: %d\n", num, len);
    }

    if (len)
    {
        printf("at %d: rec is %ld %d %d %d\n", getClk(), p_rec.id, p_rec.arrival, p_rec.runtime, p_rec.priority);
        printf("at %d: PQ front is %ld %d %d %d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
        printf("at %d: PQ front next is %ld %d %d %d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.priority);

        if (PQ->next->data.state == RESUMED || PQ->next->data.state == STARTED)
        {
            kill(pid[num - 1], SIGSTOP); // stop the running process
            if (PQ->next->data.state == STARTED)
                PQ->next->data.remain = PQ->next->data.runtime - (getClk() - PQ->next->data.ST);
            // else if(PQ->data.state = RESUMED)
            //     PQ->data.remain =
            PQ->next->data.state = STOPPED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstopped\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->next->data.id, PQ->next->data.arrival, PQ->next->data.runtime, PQ->next->data.remain, PQ->next->data.wait);
            fclose(fp);
        }

        pid[num] = fork();
        if (pid[num] == 0)
        {
            PQ->data.pid = pid[num];
            char line[20];
            sprintf(line, "./process.out %d", PQ->data.runtime);
            system(line);
            kill(getppid(), SIGUSR2);
            exit(7);
        }

        if (PQ->data.state == ARRIVED)
        {
            PQ->data.ST = getClk();
            PQ->data.wait = PQ->data.ST - PQ->data.arrival;
            PQ->data.state = STARTED;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tstarted\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        printf("prev pid: %d, curr pid: %d\n\n", pid[num - 1], pid[num]);

        if (PQ->data.state == STOPPED)
        {
            kill(PQ->data.pid, SIGCONT);
            PQ->data.state = RESUMED;
            PQ->data.wait = getClk() - ((PQ->data.runtime - PQ->data.remain) + PQ->data.arrival);
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tresumed\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait);
            fclose(fp);
        }

        // int options = *allSent ? 0 : 1 | WNOHANG;
        // my_pause();
        // sleep(1);
        ch_pid = waitpid(PQ->data.pid, &stat_loc, 0 | WNOHANG);
        if (ch_pid != 0 && !(stat_loc & 0x00FF))
        {
            printf("\nA child with pid %d terminated with exit code %d\n", ch_pid, stat_loc >> 8);
            PQ->data.remain = 0;

            PQ->data.state = FINISHED;
            int TA = getClk() - PQ->data.ST;
            PQ->data.wait = TA - PQ->data.runtime;
            W[PQ->data.id] = PQ->data.wait;

            if (PQ->data.runtime != 0)
                WTA[PQ->data.id] = TA / PQ->data.runtime;
            fp = fopen("scheduler.log", "a");
            fprintf(fp, "#At time\t%d\tprocess\t%ld\tfinished\tarr\t%d\ttotal\t%d\tremain\t%d\twait\t%d\tTA\t%d\tWTA\t%.2f\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.remain, PQ->data.wait, TA, WTA[PQ->data.id]);
            fclose(fp);
            printf("at %d: process popped is %ld %d %d %d\n\n", getClk(), PQ->data.id, PQ->data.arrival, PQ->data.runtime, PQ->data.priority);
            pop(&PQ);
            len--;

            // calculting Total runtime and CPU util
            TRT += PQ->data.runtime;
            CPUutil = (TRT / (getClk() - firstArr)) * 100;

            // calculating Average WTA and Average waiting time
            AWTA = Average(WTA, num);
            AW = Average(W, num);

            // calculating the standard deviation of the WTA
            SD = STD(WTA, num);

            // printing into scheduler.perf
            FILE *ftp = fopen("scheduler.perf", "w");
            fprintf(ftp, "CPU utilization = %d%%\nAvg WTA = %.2f\nAvg Waiting = %.2f\nStd WTA = %.2f", CPUutil, AWTA, AW, SD);
            fclose(ftp);
        }
    }
}

void handler(int sigum)
{
    destroyClk(true);
}

int main(int argc, char *argv[])
{
    initClk();

    signal(SIGINT, handler);
    signal(SIGALRM, sigalarm_handler);

    key_t msgqid;
    msgqid = msgget(12613, IPC_CREAT | 0644);
    if (msgqid == -1)
    {
        perror("Scheduler: Error in create");
        // exit(-1);
    }

    struct details d;

    if ((msgrcv(msgqid, &d, sizeof(d), 7, !IPC_NOWAIT)) == -1)
        perror("Scheduler: Error in receiving details");

    FILE *fp;
    fp = fopen("scheduler.log", "w");
    fprintf(fp, "#At time\tx\tprocess\ty\tstate\tarr\tw\ttotal\tz\tremain\ty\twait\tk\n");
    fclose(fp);

    struct Queue *Q = createQueue();
    struct process dummy = {.state = UNDEFINED}; // used in RR
    PQ = NewNode(dummy, INT_MAX);                // used in SRTN
    int shmid = shmget(5, sizeof(int), IPC_CREAT | 0644);
    allSent = (int *)shmat(shmid, (void *)0, 0);

    switch (d.scheduling_algo)
    {
    case 1:
        /* Round Robin */
        while (1)
            roundRobin(Q, msgqid, fp, d.quantum);
        break;

    case 2:
        /* SRTN */
        while (1)
            SRTN(msgqid, fp);
        break;

    case 3:
        /* non preemptive HPF */
        while (1)
            HPF(msgqid, fp);
        break;

    default:
        break;
    }

    shmdt(allSent);
    //TODO implement the scheduler :)
    //upon termination release the clock resources
}


/* // TODO: 
    atoi - done 
    how to implement our code while in loop it blocks - done
    exit
    sending processes
    sending number of proceses or making the size static
    **Amir** send a struct containing the details(the algorithm and its parameters) or pass them as argv
    Error: sh: 1: ./process.c: Permission denied
 */