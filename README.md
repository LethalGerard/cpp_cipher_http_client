# Cipher Server CTF

You are given a template for making HTTP requests and parsing responses. Your mission is to implement a client connection using TCP sockets, retrieve the encrypted messages and decrypt them - one endpoint at the time!

---

## The Challenge

Each endpoint on the server holds a hidden message encrypted with a different cipher.
You will need to:

1. **Create a TCP socket** and connect to the server
2. **Send a HTTP request**  over the socket
3. **Read the HTTP response** and extract the JSON body
4. **Decrypt the cipher text** using the cipher algorithm and the key provided in the JSON body.

The endpoints are ordered from easiest to hardest. Start from the top and work your way down.

---

## Connecting to the Server

**Check the board to see the server connection!**

You are **not** allowed to use a high-level HTTP library (like `requests`, `curl`, `fetch`, etc.).
You must open a raw socket and write the HTTP request yourself.

A minimal valid HTTP GET request looks like this:

```
GET /path HTTP/1.1\r\n
Host: 192.168.1.103:8080\r\n
\r\n
```

---

## Response Format

Every cipher endpoint returns a JSON body shaped like this:

```json
{
  "key": "<the key used to encrypt>",
  "cipherText": "<the encrypted message>"
}
```

The `/clear-text` endpoint returns the raw text — no JSON wrapper, no encryption.

The ciphers which doesn't need a key - will return `no key` in as their `key` value.

---

## Verify Your Setup — Test Endpoint

Before diving into the ciphers, make sure your socket code works:

```
GET /test HTTP/1.1
```

Expected response body: `anyone can see this`

If you can read that, your socket is working correctly.

---

## Endpoints — Ordered by Difficulty

### 1. `/clear-text`
No encryption. The message is returned as plain text.
This is your reference — the hidden messages on the other endpoints are inspired by the same style.

---

### 2. `/inverse-cipher`
**Cipher:** The message is reversed character by character.

---

### 3. `/rot13-cipher`
**Cipher:** ROT13 - each letter is shifted 13 places in the alphabet.

---

### 4. `/atbash-cipher`
**Cipher:** Atbash — the alphabet is reversed (`A ↔ Z`, `B ↔ Y`, ...). 


---

### 5. `/ceasar-cipher`
**Cipher:** Ceasar — each letter is shifted by a fixed number of positions. 

**Key:** `5`

---

### 6. `/base64-cipher`
**Cipher:** Base64 encoding

---

### 7. `/xor-cipher`
**Cipher:** XOR cipher — each byte of the message is XOR'd with the key byte. 

**Key:** `3`

---

### 8. `/rail-fence-cipher`
**Cipher:** Rail Fence Cipher — characters are written in a zigzag pattern across a number of "rails", then read off row by row. 

**Key:** `7`

---

### 9. `/substitution-cipher`
**Cipher:** Simple Substitution Cipher — each letter of the alphabet is mapped to a different letter according to the key. 

**Key:** `qwertyuiopasdfghjklzxcvbnm`

---

### 10. `/columnar-transposition-cipher`
**Cipher:** Columnar transposition — the message is written in rows under a keyword, then the columns are read out in the alphabetical order of the keyword letters.

**Key:** `AnaConDa`

---

### 11. `/vigenere-cipher`
**Cipher:** Vigenère cipher — a polyalphabetic substitution where each character is shifted by the corresponding character in a repeating key, modulo a given value.

**Key:** `qewqioj`  
**Mod:** `127`

---

### 12. `/affine-cipher`
**Cipher:** Affine cipher — each character value is transformed as `(a * x + b) mod m`. Decryption requires the modular inverse of `a`.

**Key:** `125,33`   
**Modulus:** `127`

---

### 13. `/monome-cipher`
**Cipher:** Monome cipher — characters are mapped through a substitution table built from the key using a modular scheme.

**Key:** `mawerhoiu`  
**Modulus:** `127`

---

### 14. `/playfair-cipher`
**Cipher:** Playfair cipher — a digraph substitution cipher using a 5×5 grid built from the keyword. Characters are encrypted in pairs.

**Key:** `StuxNet`

---

## Tips

- Parse the HTTP response carefully — the body starts after the first blank line (`\r\n\r\n`).
- The JSON fields are always `"key"` and `"cipherText"`.
- The server returns `404 Not Found` for unknown endpoints and `501 Not Implemented` for non-GET requests.
- If decryption produces garbled output, double-check your modulus arithmetic — off-by-one errors are common.
- When in doubt, look up the Wikipedia article for the cipher — the algorithm description is usually enough to implement decryption.

Good luck.
