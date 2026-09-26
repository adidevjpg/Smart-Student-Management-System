// Smart Student Management System - Frontend Interactivity

document.addEventListener('DOMContentLoaded', () => {
    // 1. Automatically populate current copyright year
    const yearSpan = document.getElementById('year');
    if (yearSpan) {
        yearSpan.textContent = new Date().getFullYear();
    }

    // 2. Responsive mobile hamburger menu toggle
    const menuBtn = document.getElementById('menuBtn');
    const navMenu = document.getElementById('navMenu');

    if (menuBtn && navMenu) {
        menuBtn.addEventListener('click', () => {
            navMenu.classList.toggle('active');
        });

        // Close mobile navigation menu when a link is clicked
        const navLinks = navMenu.querySelectorAll('a');
        navLinks.forEach(link => {
            link.addEventListener('click', () => {
                navMenu.classList.remove('active');
            });
        });
    }
});
