// Grab encrypted text from URL query
const params = new URLSearchParams(window.location.search);
const text = params.get('text');

const encryptedTextDiv = document.getElementById("encrypted-text");
if(text) {
  encryptedTextDiv.textContent = text;
}