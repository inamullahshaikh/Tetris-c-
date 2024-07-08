// Inam Ullah Shaikh 22i-0857 Sec H End of semester Project
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
using namespace std;
int main(){
srand(time(0));
//<---creation of starting menu--->
RenderWindow menu(VideoMode(320, 480), title);
Texture menuback;
menuback.loadFromFile("sources/menu.png");// loading menu.png into the tecture
Sprite background2(menuback);
menu.draw(background2);
menu.display(); 
while (menu.isOpen()){
Event m;
while (menu.pollEvent(m)){  
if (m.type == Event::Closed)                   
menu.close();    
if (m.type == Event::KeyPressed) {             
if (m.key.code == Keyboard::Enter)      //When Enter key is pressed menu is closed
menu.close(); }
menu.clear(Color::Black);
}
}
//<---Creating music and soundeffects --->
Music music,sou,endop;           
//<--- Creating window in which the game will be played--->
RenderWindow window(VideoMode(320, 480), title);; 
Texture obj1, obj2, obj3, obj4;
obj1.loadFromFile ( "sources/tiles.png");
obj2.loadFromFile ( "sources/background.png");
obj3.loadFromFile ("sources/frame.png");
obj4.loadFromFile("sources/tiles.png");
Sprite sprite(obj1), background(obj2), frame(obj3), shade(obj4);
int delta_x=0, colorNum=3, s = 0;
float timer=0, delay=0.4,tlc=300;
bool rotate=0,end;
Clock clock,xytr;
music.openFromFile("sources/song.ogg"); // Loading soundtrack which runs until the game runs
music.setVolume(50);
music.play();
while (window.isOpen()){ 
float time = clock.getElapsedTime().asSeconds();
float tc = xytr.getElapsedTime().asSeconds();
clock.restart();
timer+=time;
Event e;
//<---Checking which key is pressed--->
while (window.pollEvent(e)){                   
if (e.type == Event::Closed)                   
window.close();                            
if (e.type == Event::KeyPressed) {             
if (e.key.code == Keyboard::Up)// if Up is pressed rotation starts and a sound effect is played        
{
sou.openFromFile("sources/se.ogg");
sou.setVolume(30);
sou.play();rotate = true;
rotationaboutaxis(rotate);
}
else if (e.key.code == Keyboard::Left)// if Left is pressed movement towards left starts and a sound effect is played      
{
sou.openFromFile("sources/se.ogg");
sou.setVolume(30);
sou.play();
delta_x = -1; 
movelr(delta_x);
}                         
else if (e.key.code == Keyboard::Right)// if Right is pressed movement towards right starts and a sound effect is played     
{
sou.openFromFile("sources/se.ogg");
sou.setVolume(30);
sou.play();
delta_x = 1;
movelr(delta_x);
}                          
else if (e.key.code == Keyboard::Down)// if Down is pressed delay is reduced and piece falls down quickly and a sound effect is played 
{
sou.openFromFile("sources/se.ogg");
sou.setVolume(30);
sou.play(); 
delay=0.01;
}                              
else if (e.key.code == Keyboard::Space)// If Space is pressed delay is reduced and piece falls down instantly and a sound effect is played
{
sou.openFromFile("sources/se.ogg");
sou.setVolume(30);
sou.play(); 
space();
}
else if(Keyboard::isKeyPressed(Keyboard::Escape))// If Esc is pressed a pause menu is created and displayed
{
RenderWindow pause(VideoMode(320, 480), title);
Texture menu;
menu.loadFromFile("sources/pause.png");
Sprite xy(menu);
pause.draw(xy);
pause.display(); 
while (pause.isOpen()){
Event m;
while (pause.pollEvent(m)){  
if (m.type == Event::Closed)                   
pause.close(); 
if (m.type == Event::KeyPressed) { 
if (m.key.code == Keyboard::Escape)// If Esc is pressed pause menu is closed and  game is continued           
pause.close(); }
}
}
}   
window.display();      
}            
}

//<---Calling functions--->     
fallingPiece(timer, delay, colorNum);   
trans(s);
shadow();
end = endcheck();
window.clear(Color::Black);
window.draw(background);

for (int i=0; i<M; i++){
for (int j=0; j<N; j++){
if (gameGrid[i][j]==0)
continue;
sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
shade.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
sprite.setPosition(j*18,i*18);
shade.setPosition(j*18,i*18);
sprite.move(28,31); //offsett
shade.move(28,31); //offset
window.draw(sprite);
window.draw(shade);
}
}

for (int i=0; i<4; i++){
sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
shade.setTextureRect(IntRect(13*18,0,18,18));
sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
shade.setPosition(shadow_copy[i][0]*18,shadow_copy[i][1]*18);
sprite.move(28,31);
shade.move(28,31);
window.draw(sprite);
window.draw(shade);          
}

window.draw(frame); 
//<creating words to display--->      
Font fonts;
fonts.loadFromFile("sources/OpenSans-Regular.ttf");
Text display_score,lvls;
display_score.setFont(fonts);
display_score.setString("Score: "+std::to_string(s));
display_score.setStyle(sf::Text::Bold);
display_score.setFillColor(sf::Color::White);
display_score.setPosition(230,150);
display_score.setCharacterSize(15);
lvls.setFont(fonts);
if(tc<=tlc)
lvls.setString("Level 1");
else
lvls.setString("Level 2");        
lvls.setStyle(sf::Text::Bold);
lvls.setFillColor(sf::Color::White);
lvls.setPosition(230,130);
lvls.setCharacterSize(15);
window.draw(display_score);
window.draw(lvls);                            
window.display();

if(end){
window.close();
RenderWindow endmenu(VideoMode(320, 480), title);  
Texture ending;
ending.loadFromFile("sources/ending.png");
Sprite endi(ending);
endmenu.draw(endi);
endmenu.display();
endmenu.draw(endi);
endmenu.display();
endop.openFromFile("sources/end.ogg");
endop.setVolume(70);
endop.play();                    
while (endmenu.isOpen()){
Event l;
while (endmenu.pollEvent(l)){  
if (l.type == Event::Closed)                   
endmenu.close();    
if (l.type == Event::KeyPressed) {             
if (l.key.code == Keyboard::Num1)
endmenu.close();
}
}
}
}
if(tc >tlc)        
delay=0.2;
else
delay =0.4;
}
return 0;
}
