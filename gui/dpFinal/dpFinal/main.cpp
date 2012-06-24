#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "ResourcePath.hpp"

using namespace std;

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

            if(status != 3){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                printf("%d %d\n", position.x, position.y);
                if(position.x >= 153 && position.x <= 548 && position.y >= 63 && position.y <= 98 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status != 3){
                    status = 1;
                }
                if(position.x >= 153 && position.x <= 548 && position.y >= 104 && position.y <= 139 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status != 3){
                    status = 2;
                }
                
                if((position.x < 153 || position.x > 548 || position.y < 63 || position.y > 139) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && status != 3){
                    status = 0;
                }
                
                if(position.x >= 153 && position.x <= 548 && position.y >= 163 && position.y <= 200 && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
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
                    if(event.text.unicode < 128 && status == 1){
                        userID += static_cast<char>(event.text.unicode);
                    }
                }
                if(event.type == sf::Event::TextEntered){
                    if(event.text.unicode < 128 && status == 2){
                        userPassword += static_cast<char>(event.text.unicode);
                    }
                }
            }else if(status == 3){
                likeButtonRect = likeButton.getTextureRect();
                if(likeButtonRect.contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) printf("Yes");
            
            }else{
            
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
                if(!texture.loadFromFile(resourcePath() + "over.png"))
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
    	if(status != 3){
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
            
        }
        else{   
            sf::Vector2i likeButtonPosition(153, 63);
            sf::Vector2i likeButtonSize(400, 40);
            likeButton.setPosition((sf::Vector2f)likeButtonPosition);
            likeButton.setSize((sf::Vector2f) likeButtonSize);
            likeButton.setFillColor(sf::Color::Cyan);
            likeButton.setTextureRect(sf::IntRect(likeButtonPosition, likeButtonSize));
            likeButtonString = sf::String("Who Likes Me?");
            likeButtonText.setString(likeButtonString);
            likeButtonText.setColor(sf::Color::Blue);
            likeButtonText.setCharacterSize(25);
            likeButtonText.setPosition(160, 68);
            window.draw(sprite);
            window.draw(likeButton);
            window.draw(likeButtonText);
            
        }
        // Update the window
        window.display();
    }

	return EXIT_SUCCESS;
}
