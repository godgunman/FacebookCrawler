#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ResourcePath.hpp"

using namespace std;

vector<sf::Image> loadImages();

int main (int argc, const char * argv[])
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(710, 437), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "original.png"))
    	return EXIT_FAILURE;
    sf::Sprite sprite(texture);
  
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg"))
    	return EXIT_FAILURE;

    // Play the music
    music.play();
    int status;
    sf::String userID;
    sf::String userPassword;
    sf::Text idText;
    sf::Text passwordText;
    sf::RectangleShape likeButton;
    sf::Text likeButtonText;
    sf::IntRect likeButtonRect;
    sf::String likeButtonString;
    
    // Start the game loop
    while (window.isOpen())
    {
    	// Process events
    	sf::Event event;
        

        //string str;
    	while (window.pollEvent(event))
    	{
    		// Close window : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
    		if (event.type == sf::Event::Closed)
                window.close();
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if(status != 3){
                printf("%d %d\n", position.x, position.y);
                if(position.x >= 153 && position.x <= 548 && position.y >= 63 && position.y <= 98 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status < 3){
                    status = 1;
                }
                if(position.x >= 153 && position.x <= 548 && position.y >= 104 && position.y <= 139 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status < 3){
                    status = 2;
                }
                
                if((position.x < 153 || position.x > 548 || position.y < 63 || position.y > 139) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status < 3){
                    status = 0;
                }
                
                if(position.x >= 153 && position.x <= 548 && position.y >= 163 && position.y <= 200 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status != 4){
                    if(userPassword.getSize() > 0 && userID.getSize() > 0) status = 3;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Back)){
                    if(status == 1){
                        if(userID.getSize() > 0) userID.erase(userID.getSize()-1);
                    }
                    if(status == 2){
                        if(userPassword.getSize() > 0) userPassword.erase(userPassword.getSize()-1);
                    }
                }
                if(event.type == sf::Event::TextEntered){
                    if(status == 1){
                        userID += static_cast<char>(event.text.unicode);
                    }
                }
                if(event.type == sf::Event::TextEntered){
                    if(event.text.unicode < 128 && status == 2){
                        userPassword += static_cast<char>(event.text.unicode);
                    }
                }
            }else if(status == 3){
                if(position.x >= 153 && position.x <= 548 && position.y >= 163 && position.y <= 200 && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    status = 4;
                }
            }else{
                ;
            }
            
        }
        
        switch (status) {
            case 1:
                if(!texture.loadFromFile(resourcePath() + "clickup.png"))
                    return EXIT_FAILURE;
                sprite.setTexture(texture);
                break;
            case 2:
                if(!texture.loadFromFile(resourcePath() + "clickdown.png"))
                    return EXIT_FAILURE;
                sprite.setTexture(texture);
                break;
            case 3:
                if(!texture.loadFromFile(resourcePath() + "button.png"))
                    return EXIT_FAILURE;
                sprite.setTexture(texture);
                break;
            case 4:
                if(!texture.loadFromFile(resourcePath() + "likes_graph.png"))
                    return EXIT_FAILURE;
                sprite.setTexture(texture);
                break;
            default:
                if (!texture.loadFromFile(resourcePath() + "original.png"))
                    return EXIT_FAILURE;
                sprite.setTexture(texture);
                break;
        }
        
    	// Clear screen
    	
    	window.clear();
    	// Draw the sprite
    	if(status < 3){
            window.draw(sprite);
            // Draw the string
            
            idText.setString(userID);
            idText.setPosition(160, 68);
            idText.setColor(sf::Color::Black);
            idText.setCharacterSize(20);
            if(userID.getSize() != 0) window.draw(idText);
            sf::String tmp = sf::String(userPassword);
            for(int i = 0; i < userPassword.getSize(); i++) tmp[i] = 9679;
            passwordText.setString(tmp);
            passwordText.setPosition(160, 110);
            passwordText.setColor(sf::Color::Black);
            passwordText.setCharacterSize(20);
            if(userPassword.getSize() != 0) window.draw(passwordText);
            
        }else if(status == 4)
        {
            //TODO!!!!!
            vector<sf::Image> images = loadImages();
            vector<sf::Texture> textures;
            vector<sf::Sprite> sprites;
            sprites.resize(10);
            textures.resize(10);
            for(int i = 0; i < 10; i++){
                textures[i].loadFromImage(images[i]);
                sprites[i].setTexture(textures[i]);
                //set sprites position, size;
            }
            window.draw(sprite);
        }
        else{ 
            window.draw(sprite);
        }
        // Update the window
        window.display();
    }

	return EXIT_SUCCESS;
}

vector<sf::Image> loadImages(){
    vector<sf::Image> images;
    for(int i = 0; i < 10; i++){
        sf::Image tmp;
        tmp.loadFromFile("");
    }
    return images;
}