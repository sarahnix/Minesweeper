#include "GameManager.h"

void GameManager::run() {
    sf::RenderWindow window(sf::VideoMode(board.width, board.height), "Minesweeper");
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (board.face.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        board.reset();
                    }
                    else if (board.debug.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (!board.over) {
                            board.pressed = !board.pressed;
                            board.toggleMines();
                        }
                    }
                    else if (board.test1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        board.readBoard("boards/testboard1.brd");
                    }
                    else if (board.test2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        board.readBoard("boards/testboard2.brd");
                    }
                    else if (board.test3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        board.readBoard("boards/testboard3.brd");
                    }
                    else if ((!board.over)) {
                        board.number = 0;
                        for (int i = 0; i < board.getTiles().size(); i++) {
                            if (board.getTiles().at(i).back.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                board.getTiles().at(i).revealTile();
                                if (board.getTiles().at(i).isMine) {
                                    board.lost();
                                }
                            }
                        }
                        for (int i = 0; i < board.tileCount; i++) {
                            if (!board.getTiles().at(i).isMine) {
                                if (board.getTiles().at(i).isClicked) {
                                    board.number++;
                                    if (board.number == (board.tileCount - board.numMines)) {
                                        board.win();
                                    }
                                }
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if ((!board.over)) {
                        for (int i = 0; i < board.getTiles().size(); i++) {
                            if (board.getTiles()[i].back.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (board.getTiles()[i].isFlag) {
                                    board.getTiles()[i].removeFlag();
                                    board.countMines++;
                                } else if (!board.getTiles()[i].isFlag) {
                                    board.getTiles()[i].flagIt();
                                    board.countMines--;
                                }
                            }
                        }
                    }
                }
            }
        }
        window.clear();
        board.Draw(window);
        window.display();
    }
}
