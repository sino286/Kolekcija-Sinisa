#pragma once

#include <string>
#include <vector>
#include <stack>
class HTMLCompositeTag;
class CompositeIterator;

// Component klasa.
class HTMLComponent{
public:
    HTMLComponent(){}
    virtual ~HTMLComponent(){}

    virtual HTMLCompositeTag* getComposite(){ return nullptr; }
    virtual std::string getTagName() = 0;
    virtual void setTagName(std::string tagName) = 0;
    virtual std::string getStartTag() = 0;
    virtual std::string getEndTag() = 0;
    virtual std::string getBody() = 0;
    virtual void setBody(std::string body) = 0;
    virtual std::string generateHTML() = 0;
    virtual CompositeIterator iterator();
};

// List klasa 
class HTMLTag : public HTMLComponent{
public:
   HTMLTag(std::string tagName, std::string body);

   virtual std::string getTagName() override;
   virtual void setTagName(std::string tagName) override;
   virtual std::string getStartTag() override;
   virtual std::string getEndTag() override;
   virtual std::string getBody() override;
   virtual void setBody(std::string body) override;
   virtual std::string generateHTML() override;

private:
   std::string mTagName;
   std::string mBody;
};

// List klasa 
class HTMLText : public HTMLComponent{
public:
   HTMLText(std::string body);

   virtual std::string getTagName() override;
   virtual void setTagName(std::string tagName) override;
   virtual std::string getStartTag() override;
   virtual std::string getEndTag() override;
   virtual std::string getBody() override;
   virtual void setBody(std::string body) override;
   virtual std::string generateHTML() override;

private:
   std::string mBody;
};

// Composite klasa
class HTMLCompositeTag : public HTMLComponent{
public: 
    HTMLCompositeTag(std::string tagName);

    virtual HTMLCompositeTag* getComposite(){ return this; }

    virtual std::string getTagName() override;
    virtual void setTagName(std::string tagName) override;
    virtual std::string getStartTag() override;
    virtual std::string getEndTag() override;
    virtual std::string getBody() override;
    virtual void setBody(std::string body) override;
    virtual std::string generateHTML() override;
    virtual CompositeIterator iterator() override;

    void addComponent(HTMLComponent* cmp);
    void removeComponent(std::size_t index);
    HTMLComponent* getComponent(std::size_t index);
    HTMLComponent* getLastComponent();

private:
    std::vector<HTMLComponent*> mChildren;
    std::string mTagName;
};


class Iterator
{
public:
    Iterator(){}
    virtual ~Iterator(){}

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual HTMLComponent& currentItem() const = 0;
};


class CompositeIterator : public Iterator{
public:
    CompositeIterator(HTMLCompositeTag* root);

    virtual void first() override;
    virtual void next() override;
    virtual bool isDone() override;
    virtual HTMLComponent& currentItem() const override;
private:
    size_t mBegin;
    HTMLCompositeTag* mFirst;
    HTMLCompositeTag* mRoot;
    bool mKorijen;
    bool mZadnji = false;
    bool mDone = false;
    std::stack<std::pair<size_t, HTMLCompositeTag*>> mStog;
};

