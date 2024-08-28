const _C = document.querySelector(".slider-container");
const N = _C.children.length;
_C.style.setProperty("--n", N);

let x0 = null;
let locked = false;
let i = 0; 
let w; 
let interval; 

function lock(e) {
  x0 = unify(e).clientX;
  _C.classList.toggle("smooth", !(locked = true));
  _C.classList.toggle("color", (locked = true));
}

function size() {
  w = window.innerWidth;
}

function move(e) {
  if (locked) {
    let dx = unify(e).clientX - x0;
    let s = Math.sign(dx);
    let f = +((s * dx) / w).toFixed(2);

    if ((i > 0 || s < 0) && (i < N - 1 || s > 0) && f > 0.2) {
      _C.style.setProperty("--i", (i -= s));
      f = 1 - f;
    }

    _C.style.setProperty("--tx", "0px");
    _C.style.setProperty("--f", f);
    _C.classList.toggle("smooth", !(locked = false));
    _C.classList.toggle("color", (locked = false));
    x0 = null;
  }
}

size();
addEventListener("resize", size, false);

function drag(e) {
  e.preventDefault();
  if (locked) {
    _C.style.setProperty("--tx", `${Math.round(unify(e).clientX - x0)}px`);
  }
}

function switchSlide() {
  if (i + 1 < N) {
    _C.style.setProperty("--i", ++i);
  } else {
    i = 0;
    _C.style.setProperty("--i", i);
  }
}

function startAutoSlide() {
  interval = setInterval(switchSlide, 3000); // Change slide every 3 seconds
}

function stopAutoSlide() {
  clearInterval(interval);
}

let prev = document.querySelector(".prev");
let next = document.querySelector(".next");

prev.addEventListener("click", () => {
  if (i > 0) {
    _C.style.setProperty("--i", --i);
  }
  if (i == 0) {
    setTimeout(() => prev.classList.add("flash"), 100);
    prev.classList.remove("flash");
  }
  stopAutoSlide(); 
});

next.addEventListener("click", () => {
  if (i + 1 < N) {
    _C.style.setProperty("--i", ++i);
  }
  if (i + 1 == N) {
    setTimeout(() => next.classList.add("flash"), 500);
    next.classList.remove("flash");
  }
  stopAutoSlide();
});

_C.addEventListener("mousemove", drag, false);
_C.addEventListener("touchmove", drag, false);
_C.addEventListener("mousedown", lock, false);
_C.addEventListener("touchstart", lock, false);
_C.addEventListener("mouseleave", move, false);
_C.addEventListener("mouseup", move, false);
_C.addEventListener("touchend", move, false);


_C.addEventListener("touchmove", (e) => e.preventDefault(), false);


function unify(e) {
  return e.changedTouches ? e.changedTouches[0] : e;
}

startAutoSlide();
