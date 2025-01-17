#include "Render.h"

#include <iostream>
#include "UIPanel.h"
#include "MapPanel.h"
#include "TextBox.h"
#include "Panel.h"

namespace render{
    sf::Color cluedoRed(180, 0, 0);   // Rouge Cluedo
    sf::Color cluedoBlue(0, 64, 128); // Bleu Cluedo
    sf::Color cluedoLightBlue(61,173,243); // Bleu clair Cluedo
    sf::Color cluedTurquoise(0, 128, 128); // Turquoise Cluedo
    sf::Color cluedoBeige(191, 128, 128); // Beige Cluedo
    sf::Color cluedoGreenGray(132, 145, 134); // Gris vert Cluedo

Render::Render(): window(sf::VideoMode(800, 600), "Cluedo plt"), desktop(sf::VideoMode::getDesktopMode())
{
    window.clear(sf::Color::White);
    
    std::cout << desktop.width << "x" << desktop.height << std::endl;
    // Create the window
    int windowWidth = desktop.width*0.9;
    int windowHeight = desktop.height*0.9;
    window.create(sf::VideoMode(windowWidth, windowHeight), "Cluedo plt", sf::Style::Close);
    window.setFramerateLimit(120); // Réduit la charge sur le processeur.
    window.setPosition(sf::Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));
    
    //Splitting the window in two parts, one for the map and the other for the UI
    // Each part is a panel
    auto uiPanel = std::make_unique<UIPanel>(0, 0, windowWidth-windowHeight, windowHeight, cluedoRed);
    auto mapPanel = std::make_unique<MapPanel>(1, 2, windowWidth-windowHeight, 0, windowHeight, windowHeight, sf::Color::White, *map);
    this->addChild(std::move(uiPanel));
    this->addChild(std::move(mapPanel));
}
    void Render::draw(sf::RenderWindow &window)
    {
        this->drawChildren(window);
    }

    void Render::updateWindow() {
        if(window.isOpen()){
            sf::Event event;
            if (window.pollEvent(event)){
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }
            draw(window);
            window.display();
        }
    }

    void Render::setPlayer(client::HumanPlayerRender &player) {
        this->player = &player;
    }

    void Render::setEngine(engine::Engine &engine) {
        this->engine = &engine;
    }

    void Render::setMap(state::Map &map) {
        this->map = &map;
    }

    void Render::setPlayerStateVec(std::vector<state::PlayerState> &playerStateVec) {
        this->playerStateVec = &playerStateVec;
    }

    int Render::introductionToTheGame() {

    }

    void Render::startOfTheGame() {

    }

    void Render::diceThrow() {

    }

    void Render::updatePlayerPositions() {

    }

    void Render::displayHypothesis(const client::Player &player, const state::TripleClue &hypothesis) {

    }

    void Render::displayAccusation(const client::Player &player, const state::TripleClue &accusation) {

    }

    void Render::displayGameEnd(const client::Player &winner) {

    }


    engine::CommandId Render::chooseAction() {

    }

    engine::Move Render::chooseMoveDirection() {

    }

    state::Door &Render::chooseDoor(const std::vector<state::Door *> &doorList) {

    }


    state::TripleClue Render::chooseHypothesis() {

    }

    int Render::chooseACardToShowPlayer(const std::vector<const state::Card *> &cards, const client::Player &player) {

    }

    void Render::seeACardFromPlayer(const state::Card &shownCard, const client::Player &cardOwner) {

    }

    state::TripleClue Render::chooseAccusation() {

    }

    void Render::makePlayerThrowDice() {

    }

    void Render::displayDiceResult(int result, const client::Player &player) {

    }





}
    /*UIBackground = sf::RectangleShape(sf::Vector2f(abs(windowHeight-windowWidth), windowHeight));
    UIBackground.setPosition(0, 0);
    UIBackground.setFillColor(cluedoRed);
    MapBackground = sf::RectangleShape(sf::Vector2f(windowHeight, windowHeight));
    MapBackground.setPosition(windowWidth-windowHeight, 0);
    MapTexture.loadFromFile("../ressources/maison_map.png");
    MapSprite.setTexture(MapTexture);
    MapSprite.setPosition(sf::Vector2f(windowWidth-windowHeight, 0));  
    MapSprite.setScale((float)windowHeight/MapTexture.getSize().x, (float)windowHeight/MapTexture.getSize().y);  
    */
    // Setting up the grid above the map
    /*RenderMap grid(27, 26, MapBackground.getSize().x, MapBackground.getSize().y);
    grid.setPosition(windowWidth-windowHeight, 0);
    grid.mergeFromJson("../configurations/map.json");*/

    //test de textbox
    //TextBox test(sf::Vector2f(200, 50), "../ressources/fonts/Futura-Condensed-Extra-Bold.ttf", "Test");

    /*while (window.isOpen()){    
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                /*if (event.mouseButton.button == sf::Mouse::Left){
                    grid.placePiece(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), cluedoRed);
                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    grid.deletePiece(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                }
            }

        }
        window.clear(sf::Color::White);
        //window.draw(MapSprite);
        //grid.draw(window);
        //test.draw(window);
        
        window.display();
        
    }*/
    /*window.setPosition(sf::Vector2i(desktop.,0));
    window.setSize(sf::Vector2u(desktop.height, desktop.height));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60); // Réduit la charge sur le processeur.
    Background.setScale(desktop.height, desktop.height);
    sf::Vector2u textureSize = BackgroundTexture.getSize();
    std::cout << textureSize.x << "x" << textureSize.y << std::endl;

}
void Render::loadMapImage(std::string mapImagePath)
{
  
}
void Render::gameInit()
{
    sf::Font font;
    if (!font.loadFromFile("../ressources/fonts/Futura-Condensed-Extra-Bold.ttf")) {
        std::cerr << "Error loading font\n";
        window.close();
        return;
    }
    // Welcome Text
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("Bienvenue dans le jeu Cluedo");
    welcomeText.setCharacterSize(50); // in pixels, not points!
    welcomeText.setFillColor(sf::Color::Black);

    // Center the text
    sf::FloatRect textRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    welcomeText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    window.draw(welcomeText);

    // First interaction
    sf::Text questionText;
    questionText.setFont(font);
    questionText.setString("Press Space to start the game");
    questionText.setCharacterSize(30); // in pixels, not points!
    questionText.setFillColor(sf::Color::Black);

    // Center the text
    textRect = questionText.getLocalBounds();
    questionText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    questionText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50);

    window.draw(questionText);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    window.clear(sf::Color::White);
                    gameSetUp();
                    window.display();
                }
            }
        }
        window.display();
    }

}
void Render::gameSetUp()
{
    sf::Font font;
    if (!font.loadFromFile("../ressources/fonts/Futura-Condensed-Extra-Bold.ttf")) {
        std::cerr << "Error loading font\n";
        window.close();
        return;
    }
    // Setting Text
    sf::Text settingsText;
    settingsText.setFont(font);
    settingsText.setString(L"Définissons les paramètres du jeu");
    settingsText.setCharacterSize(24); // in pixels, not points!
    settingsText.setFillColor(sf::Color::Black);

    // Put the text in top left corner
    sf::FloatRect textRect = settingsText.getLocalBounds();
    settingsText.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + textRect.height / 2.0f);
    settingsText.setPosition(200, 50);

    // Bouton déroulant
    std::vector<std::string> suspects = {"Moutarde", "Rose", "Pervenche", "Olive", "Violet", "Leblanc"};
    std::vector<sf::Text> suspectTexts;
    std::vector<sf::RectangleShape> suspectBoxes;
    std::vector<sf::Text> nameInputs;

    for (size_t i = 0; i < 3; ++i) { // Start with 3 players
        sf::Text suspectText;
        suspectText.setFont(font);
        suspectText.setString("Suspect");
        suspectText.setCharacterSize(20);
        suspectText.setFillColor(sf::Color::Black);
        suspectText.setPosition(200, 200 + i * 60);
        suspectTexts.push_back(suspectText);

        sf::RectangleShape suspectBox(sf::Vector2f(200, 30));
        suspectBox.setFillColor(sf::Color::White);
        suspectBox.setOutlineColor(sf::Color::Black);
        suspectBox.setOutlineThickness(1);
        suspectBox.setPosition(400, 200 + i * 60);
        suspectBoxes.push_back(suspectBox);

        sf::Text nameInput;
        nameInput.setFont(font);
        nameInput.setString("Enter name");
        nameInput.setCharacterSize(20);
        nameInput.setFillColor(sf::Color::Black);
        nameInput.setPosition(410, 205 + i * 60);
        nameInputs.push_back(nameInput);
    }
    // Dropdown for selecting the number of players
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (size_t i = 0; i < suspectBoxes.size(); ++i)
                    {
                        if (suspectBoxes[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            std::cout << "Suspect box clicked: " << suspects[i] << std::endl;
                            // Add your logic to handle suspect selection here
                        }
                    }
                }
            }              
        }
        window.clear(sf::Color::White);
        window.draw(settingsText);
        for (size_t i = 0; i < suspectTexts.size(); ++i) {
            window.draw(suspectTexts[i]);
            window.draw(suspectBoxes[i]);
            window.draw(nameInputs[i]);
        }
        window.display();
    }
}
*/
    
    // Button to add a player
    /*sf::RectangleShape addButton(sf::Vector2f(200, 50));
    addButton.setFillColor(cluedoRed);
    addButton.setPosition(200, 100);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Ajouter un joueur");
    buttonText.setCharacterSize(20); // in pixels, not points!
    buttonText.setFillColor(sf::Color::White);

    // Center the text on the button
    sf::FloatRect buttonTextRect = buttonText.getLocalBounds();
    buttonText.setOrigin(buttonTextRect.left + buttonTextRect.width / 2.0f,
                         buttonTextRect.top + buttonTextRect.height / 2.0f);
    buttonText.setPosition(addButton.getPosition().x + addButton.getSize().x / 2.0f,
                           addButton.getPosition().y + addButton.getSize().y / 2.0f);

    window.draw(addButton);
    window.draw(buttonText);

    // Suspect selection
    std::vector<std::string> suspects = {"Colonel Mustard", "Miss Scarlet", "Professor Plum", "Mr. Green", "Mrs. Peacock", "Mrs. White"};
    std::vector<sf::Text> suspectTexts;
    std::vector<sf::RectangleShape> suspectBoxes;
    std::vector<sf::Text> nameInputs;

    for (size_t i = 0; i < 3; ++i) { // Start with 3 players
        sf::Text suspectText;
        suspectText.setFont(font);
        suspectText.setString(suspects[i]);
        suspectText.setCharacterSize(20);
        suspectText.setFillColor(sf::Color::Black);
        suspectText.setPosition(200, 200 + i * 60);
        suspectTexts.push_back(suspectText);

        sf::RectangleShape suspectBox(sf::Vector2f(200, 30));
        suspectBox.setFillColor(sf::Color::White);
        suspectBox.setOutlineColor(sf::Color::Black);
        suspectBox.setOutlineThickness(1);
        suspectBox.setPosition(400, 200 + i * 60);
        suspectBoxes.push_back(suspectBox);

        sf::Text nameInput;
        nameInput.setFont(font);
        nameInput.setString("Enter name");
        nameInput.setCharacterSize(20);
        nameInput.setFillColor(sf::Color::Black);
        nameInput.setPosition(410, 205 + i * 60);
        nameInputs.push_back(nameInput);
    }
    // Dropdown for selecting the number of players
    sf::RectangleShape dropdownBox(sf::Vector2f(200, 30));
    dropdownBox.setFillColor(sf::Color::White);
    dropdownBox.setOutlineColor(sf::Color::Black);
    dropdownBox.setOutlineThickness(1);
    dropdownBox.setPosition(200, 150);

    sf::Text dropdownText;
    dropdownText.setFont(font);
    dropdownText.setString("Select number of players");
    dropdownText.setCharacterSize(20);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition(210, 155);

    window.draw(dropdownBox);
    window.draw(dropdownText);

    std::vector<sf::Text> dropdownOptions;
    for (int i = 3; i <= 6; ++i) {
        sf::Text option;
        option.setFont(font);
        option.setString(std::to_string(i));
        option.setCharacterSize(20);
        option.setFillColor(sf::Color::Black);
        option.setPosition(210, 150 + i * 30);
        dropdownOptions.push_back(option);
    }

    bool dropdownOpen = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (addButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        size_t i = suspectTexts.size();
                        if (i < suspects.size()) {
                            sf::Text suspectText;
                            suspectText.setFont(font);
                            suspectText.setString(suspects[i]);
                            suspectText.setCharacterSize(20);
                            suspectText.setFillColor(sf::Color::Black);
                            suspectText.setPosition(200, 200 + i * 60);
                            suspectTexts.push_back(suspectText);

                            sf::RectangleShape suspectBox(sf::Vector2f(200, 30));
                            suspectBox.setFillColor(sf::Color::White);
                            suspectBox.setOutlineColor(sf::Color::Black);
                            suspectBox.setOutlineThickness(1);
                            suspectBox.setPosition(400, 200 + i * 60);
                            suspectBoxes.push_back(suspectBox);

                            sf::Text nameInput;
                            nameInput.setFont(font);
                            nameInput.setString("Enter name");
                            nameInput.setCharacterSize(20);
                            nameInput.setFillColor(sf::Color::Black);
                            nameInput.setPosition(410, 205 + i * 60);
                            nameInputs.push_back(nameInput);
                        }
                    }
                    for (size_t i = 0; i < suspectBoxes.size(); ++i) {
                        if (suspectBoxes[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            std::cout << "Suspect box clicked: " << suspects[i] << std::endl;
                            // Add your logic to handle suspect selection here
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(settingsText);
        window.draw(addButton);
        window.draw(buttonText);
        for (size_t i = 0; i < suspectTexts.size(); ++i) {
            window.draw(suspectTexts[i]);
            window.draw(suspectBoxes[i]);
            window.draw(nameInputs[i]);
        }
        window.display();
    }

void Render::suspectDropDown(float firstButtonX, float firstButtonY, std::vector<std::string> suspectList)
{
    /*sf::Font font;
    if (!font.loadFromFile("../ressources/fonts/Futura-Condensed-Extra-Bold.ttf")) {
        std::cerr << "Error loading font\n";
        window.close();
        return;
    }

    // Suspect selection
    std::vector<sf::Text> suspectNamesTexts;
    std::vector<sf::RectangleShape> suspectBoxes;

    for (size_t i = 0; i < 3; ++i) { // Start with 3 players
        sf::Text suspectNameText;
        suspectText.setFont(font);
        suspectText.setString(SuspectList[i]);
        suspectText.setCharacterSize(20);
        suspectText.setFillColor(sf::Color::Black);
        suspectText.setPosition(FirstButtonX, FirstButtonY + i * 60);
        suspectTexts.push_back(suspectText);^
        }*/