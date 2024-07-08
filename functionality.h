void fallingPiece(float& timer, float& delay, int& colorNum)
{
if (timer>delay)
{
for (int i=0;i<4;i++)
{
point_2[i][0]=point_1[i][0];
point_2[i][1]=point_1[i][1];
point_1[i][1]+=1;  
}
if (anamoly()==0)
{
for (int i=0; i<4; i++)
gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
colorNum=1+rand()%7;
int n=rand()%7;  
for (int i=0;i<4;i++)
{  
point_1[i][0] = BLOCKS[n][i] % 2;
point_1[i][1] = BLOCKS[n][i] / 2;
}         
}
timer=0;
}
}

void movelr(int& delta_x)
{
for (int i=0;i<4;i++)
point_1[i][0] = point_1[i][0] + delta_x ;
if (anamoly()==0)
{
for (int i=0;i<4;i++) 
point_1[i][0]=point_2[i][0];
} 	            	
}

bool endcheck()
{
int c = 0;
for(int i = 0 ; i < N; i++){
if(gameGrid[0][i] != 0)
   c++;
}
if(c)
return 1;
else
return 0;
}

void shadow()
{
for (int i=0;i<4;i++)
{
shadow_copy[i][0]=point_1[i][0];
shadow_copy[i][1]=point_1[i][1];
}
while (shadow_anamoly()== 1) 
{
for (int i=0;i<4;i++)
{
++shadow_copy[i][1];
}
}
}

void space()
{
for (int i=0; i<4; i++)
{
point_1[i][0]=shadow_copy[i][0];
point_1[i][1]=shadow_copy[i][1];
}
for (;anamoly() == 0;)
{
for (int i=0; i<4; i++)
{  
shadow_copy[i][1]++;
}
}
}

void trans(int & score_total)
{
int prevline = M - 1,scounter=0;
for (int i = M - 1; i > 0; i--)
{
int block_counter = 0;
for (int j = 0; j < N; j++)
{
if (gameGrid[i][j])
block_counter++;
gameGrid[prevline][j] = gameGrid[i][j];
if(block_counter == 10)
scounter++;
}
if(block_counter<N)
prevline--;
}
switch(scounter)
{
case 1 :
score_total += 10;
break; 
case 2 :
score_total += 30;
break;
case 3 :
score_total += 60;
break;
case 4 :
score_total += 100;
break;
}
}

void rotationaboutaxis(bool x)
{
if(x){
int center_x_axis,center_y_axis ;
center_x_axis=point_1[1][0];
center_y_axis=point_1[2][1];
for (int i=0;i<4;i++)
{
int x = point_1[i][1]-center_y_axis;
int y = point_1[i][0]-center_x_axis;
point_1[i][1]=center_y_axis+y;
point_1[i][0]=center_x_axis-x;
}if(anamoly()==0)
{
for(int i=0;i<4;i++)
{
point_1[i][1]=point_2[i][1];
point_1[i][0]=point_2[i][0];
}
}
}
}
