# Raytracer On a Business Card

![My initials, printed by the ray tracer](/min.png)

**To run it:**

g++ -o min.exe -O3 min.cpp && min.exe > min.ppm

("-O3" is with a capital "O", not a zero)

---

After taking a look at Andrew Kensler's raytracer on a business card (inspired by Paul Heckbert's challenge in [Graphics Gems IV](https://books.google.com/books?id=CCqzMm_-WucC&pg=PA375&lpg=PA375&dq=paul+heckbert+%22minimal+ray+tracer+programming+contest%22&source=bl&ots=mvit18HKgk&sig=ACfU3U0DkBGo6Y-KX64CLLCBbKb7O6X8fA&hl=en&sa=X&ved=2ahUKEwiJhobwp7TzAhUNTt8KHdgWCNcQ6AF6BAgDEAM#v=onepage&q=paul%20heckbert%20%22minimal%20ray%20tracer%20programming%20contest%22&f=false)), I decided to try my own, based off Kensler's approach (unfortunately, I can't find a link to his original code). [Fabien Sanglard's website](https://fabiensanglard.net/rayTracing_back_of_business_card/) has a really helpful explanation of Kensler's code you can look at. Maybe it was the size of my initials, but my raytracer is a few bytes shorter. Going by what [Taylor Petrick's website](https://www.taylorpetrick.com/blog/post/business-rt) says, a standard 3.5" x 2" business card can probably fit 120 characters by 24 lines, at most. The min.cpp file is 112 characters by 17 lines, so I imagine that all the text would fit. Instead of Kensler's black to purple (zenith to horizon) gradient, I wanted a more realistic sky, where the zenith is a deep blue and the horizon is more washed out. I could not find a way to make this work without potentially adding too much extra code to fit on a business card. I settled on a black zenith, washed-out blue horizon, and a deep blue for the sky that was on screen. The black zenith is only visible in the spheres' reflections, so it's a compromise I'll be willing to settle on.

---

In case you decide you want to switch out my initials for your own, there are some things to note.
First of all, practice the design using a 19x9 grid of 1s and 0s. Put a 1 where you want a ball, and 0 everwhere else. In my case:

0000000000000000000  
0000100000000000100  
0001010000000000100  
0001010000000000100  
0010001000000000100  
0011111000100000100  
0010001000100000100  
0100000100010001000  
0100000100001110000

Now, take each of these rows and convert their value from binary to decimal and replace their value in the list called G[]. **Please note:** it's best to convert the rows from bottom to top, when replacing the values in the array. Otherwise, your text will be upsidedown! At some point, I can fix the code to traverse the array backwards so you can do things from top to bottom instead.

If you have any trouble viewing .ppm images, I was able to get Gimp to recognize it. There may be online .ppm viewers you can try, alternatively.

The program is hardcoded to 9 rows, but you can change that by increasing or decreasing the number of elements in G[] in addition to changing the starting value of j in the nested for-loop to the new size of G[]).
Similarly, you have 19 columns to work with, but can increase that by changing the starting value of i in the nested for-loop just above j.

---

All of this was done in less than a day, so it's definitely nowhere near perfect. To the best of my ability, I tried to annotate how the source code works or otherwise explain things here. The code is more fragile than you might think. Certain wrong color values can screw up the whole image, so tread carefully when experimenting with that. It also gets really dark if you set nRays to a low number (like 4 rays), and the colors get messed up if nRays is set too high (for example, 128 rays). Figuring out the camera location and angle stuff can also be a bit tricky.

# Putting it on a business card:

If you would like to fit this onto your business card, make sure you start with a 3.75" x 2.25" size image to account for the 1/8" cutoff areas on either side of the card (if your card's size is the standard 3.5" x 2"). Make your image 300dpi. I have included a template with the proper sizing and dpi and shows the 1/8" cutoff areas. If you would like to use an online business card creator in place of uploading an image, keep in mind that many places don't support fonts or sizes (6pt font) that would fit everything. I've found that zazzle.com and overnightprints.com have one or two fonts that you could make work. Alternatively, you could even use mine, though be forwarned that it displays my initials: AJ.

![The back of my business card](/business_card_back.png)
