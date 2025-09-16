document.addEventListener("DOMContentLoaded", () => {
  const title = document.querySelector(".title");
  let glow = 0;
  setInterval(() => {
    glow = (glow + 1) % 2;
    title.style.textShadow = glow 
      ? "0 0 15px #9370db, 0 0 30px #6a5acd" 
      : "0 0 10px #6a5acd, 0 0 20px #483d8b";
  }, 800);
});