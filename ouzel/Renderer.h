// Copyright (C) 2015 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "Noncopyable.h"
#include "ReferenceCounted.h"
#include "Rectangle.h"
#include "Matrix4.h"
#include "Size2.h"

namespace ouzel
{
    const std::string SHADER_TEXTURE = "shaderTexture";
    const std::string SHADER_COLOR = "shaderColor";
    
    class Engine;
    class Texture;
    class Node;
    class Shader;
    class Sprite;

    class Renderer: public Noncopyable, public ReferenceCounted
    {
    public:
        enum class Driver
        {
            NONE = 0,
            OPENGL,
            DIRECT3D11
        };
        
        Renderer(Engine* engine, Driver driver = Driver::NONE);
        virtual ~Renderer();
        
        Driver getDriver() const { return _driver; }
        
        virtual void resize(const Size2& size);
        
        virtual void clear();
        virtual void flush();
        
        void preloadTexture(const std::string& filename);
        Texture* getTexture(const std::string& filename);
        virtual Texture* loadTexture(const std::string& filename);
        virtual void activateTexture(Texture* texture, uint32_t layer);
        
        Shader* getShader(const std::string& shaderName) const;
        void setShader(const std::string& shaderName, Shader* shader);
        virtual Shader* loadShader(const std::string& fragmentShader, const std::string& vertexShader);
        virtual void activateShader(Shader* shader);
        
        const Matrix4& getProjection() const { return _projection; }
        
        Vector2 absoluteToWorldLocation(const Vector2& position);
        Vector2 worldToAbsoluteLocation(const Vector2& position);
        
        virtual void drawLine(const Vector2& start, const Vector2& finish, const Vector3& color, const Matrix4& transform = Matrix4());
        virtual void drawRectangle(const Rectangle& rectangle, const Vector3& color, const Matrix4& transform = Matrix4());
        virtual void drawQuad(const Rectangle& rectangle, const Vector3& color, const Matrix4& transform = Matrix4());
        
    protected:
        Engine* _engine;
        Driver _driver;
        
        Matrix4 _projection;
        
        Size2 _size;
        
        std::unordered_map<std::string, Texture*> _textures;
        
        std::unordered_map<std::string, Shader*> _shaders;
    };
}
