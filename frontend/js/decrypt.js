document.addEventListener("DOMContentLoaded", () => {
  const decryptBtn = document.getElementById("decrypt-btn");

  decryptBtn.addEventListener("click", () => {
    const input = document.getElementById("input-text").value;
    const key = document.getElementById("dec-key").value;
    const technique = document.getElementById("technique").value;

    if (!key) {
      alert("Key is required for decryption!");
      return;
    }

    // Simple mock decryption (replace with actual logic later)
    let decrypted = `[${technique.toUpperCase()}] ` + input.split("").reverse().join("");

    // Redirect to result page with decrypted text
    window.location.href = `result.html?text=${encodeURIComponent(decrypted)}`;
  });
});