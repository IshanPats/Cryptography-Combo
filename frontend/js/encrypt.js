document.addEventListener("DOMContentLoaded", () => {
  const encryptBtn = document.getElementById("encrypt-btn");

  encryptBtn.addEventListener("click", () => {
    const input = document.getElementById("input-text").value.trim();
    const key = document.getElementById("enc-key").value.trim();
    const technique = document.getElementById("technique").value;

    if(!input) {
      alert("Please enter text to encrypt!");
      return;
    }

    // Simple mock encryption (replace with actual logic later)
    let encrypted = `[${technique.toUpperCase()}] ` + input.split("").reverse().join("");

    // Redirect to result page with encrypted text in query string
    window.location.href = `result.html?text=${encodeURIComponent(encrypted)}`;
  });
});