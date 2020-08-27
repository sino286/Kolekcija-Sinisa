#include "composite.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<HTMLCompositeTag> root{new HTMLCompositeTag("html")};
    root->addComponent(new HTMLCompositeTag("body"));
    auto * body = root->getComponent(0)->getComposite();
    body->addComponent(new HTMLTag("p","Naslov"));
    body->addComponent(new HTMLCompositeTag("header"));
    auto * ul = body->getComponent(1)->getComposite();
    ul->addComponent(new HTMLTag("p", "Sample text"));
    ul->addComponent(new HTMLTag("p", "Sample text"));
    body->addComponent(new HTMLCompositeTag("p"));
    auto * p = body->getLastComponent()->getComposite();
    p->addComponent(new HTMLText("Ovaj tekst je "));
    p->addComponent(new HTMLTag("i","pisan italic."));

    auto html = root->generateHTML();
    std::cout << html;

    return 0;
 }

