#include <catch_amalgamated.hpp>

#include "Smtp/TokenReader.hpp"

TEST_CASE("Token reader can tokenize string") {
    SECTION("Tokenize string 1") {
        TokenReader reader("ABC-123.456-DEF");

        Token token1 = reader.take();
        Token token2 = reader.take();
        Token token3 = reader.take();
        Token token4 = reader.take();
        Token token5 = reader.take();
        Token token6 = reader.take();
        Token token7 = reader.take();

        REQUIRE(token1.getKind() == TokenKind::Text);
        REQUIRE(token1.getStr() == "ABC");
        REQUIRE(token2.getKind() == TokenKind::Hyphen);
        REQUIRE(token2.getStr() == "-");
        REQUIRE(token3.getKind() == TokenKind::Number);
        REQUIRE(token3.getStr() == "123");
        REQUIRE(token4.getKind() == TokenKind::Period);
        REQUIRE(token4.getStr() == ".");
        REQUIRE(token5.getKind() == TokenKind::Number);
        REQUIRE(token5.getStr() == "456");
        REQUIRE(token6.getKind() == TokenKind::Hyphen);
        REQUIRE(token6.getStr() == "-");
        REQUIRE(token7.getKind() == TokenKind::Text);
        REQUIRE(token7.getStr() == "DEF");
    }

    SECTION("Tokenize string 2") {
        TokenReader reader("example123@example.com");

        Token token1 = reader.take();
        Token token2 = reader.take();
        Token token3 = reader.take();
        Token token4 = reader.take();
        Token token5 = reader.take();
        Token token6 = reader.take();

        REQUIRE(token1.getKind() == TokenKind::Text);
        REQUIRE(token1.getStr() == "example");
        REQUIRE(token2.getKind() == TokenKind::Number);
        REQUIRE(token2.getStr() == "123");
        REQUIRE(token3.getKind() == TokenKind::At);
        REQUIRE(token3.getStr() == "@");
        REQUIRE(token4.getKind() == TokenKind::Text);
        REQUIRE(token4.getStr() == "example");
        REQUIRE(token5.getKind() == TokenKind::Period);
        REQUIRE(token5.getStr() == ".");
        REQUIRE(token6.getKind() == TokenKind::Text);
        REQUIRE(token6.getStr() == "com");
    }
}

TEST_CASE("Token reader can read while predicate return true") {
    TokenReader reader("example@example.com");
    std::string result;

    SECTION("Try read text") {
        reader.tryRead([](TokenReader& reader){
            reader.skip([](TokenKind kind){
                return kind == TokenKind::Text;
            });
            return true;
        }, &result);

        REQUIRE(result == "example");
    }

    SECTION("Try read text and at") {
        reader.tryRead([](TokenReader& reader){
            reader.skip([](TokenKind kind){
                return kind == TokenKind::Text || kind == TokenKind::At;
            });
            return true;
        }, &result);

        REQUIRE(result == "example@example");
    }

    SECTION("Try read all") {
        reader.tryRead([](TokenReader& reader){
            reader.skip([](TokenKind kind){
                return kind == TokenKind::Text || kind == TokenKind::At || kind == TokenKind::Period;
            });
            return true;
        }, &result);

        REQUIRE(result == "example@example.com");
    }
}

TEST_CASE("Token reader can peek next token") {
    TokenReader reader("AAA BBB");

    Token peek1 = reader.peek();
    Token take1 = reader.take();

    REQUIRE(peek1.getKind() == take1.getKind());
    REQUIRE(peek1.getStr() == take1.getStr());

    Token peek2 = reader.peek();
    Token take2 = reader.take();

    REQUIRE(peek2.getKind() == take2.getKind());
    REQUIRE(peek2.getStr() == take2.getStr());

    Token peek3 = reader.peek();
    Token take3 = reader.take();

    REQUIRE(peek3.getKind() == take3.getKind());
    REQUIRE(peek3.getStr() == take3.getStr());
}

TEST_CASE("Token reader can skip tokens with token kind and predicate") {
    TokenReader reader("AAA 123");

    SECTION("Skip token with kind") {
        reader.skip(TokenKind::Text);
        REQUIRE(reader.peek().getKind() == TokenKind::Space);
        REQUIRE(reader.peek().getStr() == " ");
    }

    SECTION("Skip token with predicate") {
        reader.skip([](TokenKind kind){
            return kind == TokenKind::Text || kind == TokenKind::Space;
        });
        REQUIRE(reader.peek().getKind() == TokenKind::Number);
        REQUIRE(reader.peek().getStr() == "123");
    }
}