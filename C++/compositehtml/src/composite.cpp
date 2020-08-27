#include "composite.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
// Vaš kod.

HTMLTag::HTMLTag(std::string tagName, std::string body) : HTMLComponent()
{
    setTagName(tagName);
    setBody(body);
}

std::string HTMLTag::getTagName()
{
    return mTagName;
}

void HTMLTag::setTagName(std::string tagName)
{
    mTagName = tagName;
}

std::string HTMLTag::getStartTag()
{
    return "<" + mTagName + ">";
}

std::string HTMLTag::getEndTag()
{
    return "</" + mTagName + ">";
}

std::string HTMLTag::getBody()
{
    return mBody;
}

void HTMLTag::setBody(std::string body)
{
    mBody = body;
}

std::string HTMLTag::generateHTML()
{
    return getStartTag() + getBody() + getEndTag() + "\n";
}



HTMLText::HTMLText(std::string body) : HTMLComponent()
{
    setBody(body);
}

std::string HTMLText::getTagName()
{
    return "text";
}

void HTMLText::setTagName(std::string tagName)
{

}

std::string HTMLText::getStartTag()
{

}

std::string HTMLText::getEndTag()
{

}

std::string HTMLText::getBody()
{
    return mBody;
}

void HTMLText::setBody(std::string body)
{
    mBody = body;
}

std::string HTMLText::generateHTML()
{
    return getBody();
}



HTMLCompositeTag::HTMLCompositeTag(std::string tagName) : HTMLComponent()
{
    setTagName(tagName);
}

std::string HTMLCompositeTag::getTagName()
{
    return mTagName;
}

void HTMLCompositeTag::setTagName(std::string tagName)
{
    mTagName = tagName;
}

std::string HTMLCompositeTag::getStartTag()
{
    return "<" + mTagName + ">";
}

std::string HTMLCompositeTag::getEndTag()
{
    return "</" + mTagName + ">";
}

std::string HTMLCompositeTag::getBody()
{

}

void HTMLCompositeTag::setBody(std::string body)
{

}

std::string HTMLCompositeTag::generateHTML()
{
    std::string tmp = getStartTag() + "\n";

    for(auto x : mChildren) tmp += x->generateHTML();

    tmp += getEndTag() + "\n";
    return tmp;
}

CompositeIterator HTMLCompositeTag::iterator()
{
    return CompositeIterator(this);
}

void HTMLCompositeTag::addComponent(HTMLComponent *cmp)
{
    mChildren.push_back(cmp);
}

void HTMLCompositeTag::removeComponent(std::size_t index)
{
    mChildren.erase(mChildren.begin() + (index));
}

HTMLComponent *HTMLCompositeTag::getComponent(std::size_t index)
{
    return mChildren[index];
}

HTMLComponent *HTMLCompositeTag::getLastComponent()
{
    return mChildren.back();
}

CompositeIterator::CompositeIterator(HTMLCompositeTag* root) : Iterator()
{
    mBegin = 0;
    mFirst = root;
    mRoot = root;
}

void CompositeIterator::first()
{
    mKorijen = true;
    mRoot = mFirst;
    mBegin = 0;
    mZadnji = false;
    mDone = false;
    mStog = std::stack<std::pair<size_t, HTMLCompositeTag*>>();
}

void CompositeIterator::next()
{
   if( mKorijen){
       mKorijen = false;
       return;
   }
   else{
       if(!mZadnji){
           if(mRoot->getComponent(mBegin) == mRoot->getLastComponent()){
               while(mRoot->getComponent(mBegin)  == mRoot->getLastComponent() && !mStog.empty()){
                   mBegin = mStog.top().first;
                   mRoot = mStog.top().second;
                   //std::cout<<"-"<<mStog.top().first<< mStog.top().second->getTagName()<<"\n";
                   mStog.pop();
                   if(mStog.size() == 0) mDone = true;

               }
               if(mRoot->getComponent(mBegin) != mRoot->getLastComponent()){
                    ++mBegin;
                    mZadnji = true;
                    return;
               }
           }
       }
       mZadnji = false;
       if(mRoot->getComponent(mBegin)->getComposite() == nullptr){
           ++mBegin;
           if(mRoot->getComponent(mBegin)->getComposite() != nullptr)
               mZadnji = true;
           return;
       }else {
           mStog.push(std::make_pair(mBegin,mRoot));
           //std::cout<<"+"<<mStog.top().first<< mStog.top().second->getTagName()<<"\n";
           mRoot = mRoot->getComponent(mBegin)->getComposite();
           mBegin = 0;

           return;
       }
    }

}

bool CompositeIterator::isDone()
{
   return mDone;
}

HTMLComponent &CompositeIterator::currentItem() const
{
    if(mKorijen)
        return *mRoot;
    else
        return *(mRoot->getComponent(mBegin));
}

CompositeIterator HTMLComponent::iterator()
{

}
