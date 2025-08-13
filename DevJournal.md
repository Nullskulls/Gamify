<h1 align="center">Journal</h1>

<h4>About:</h4>
This project was made over the span of 2-3 days honestly not sure, Plan originally was for this to be written in Java but plans changed
maybe for the better or worse who knows, All I know is that I had alot of fun experimenting with this project!

---
<h4> Day 1:</h4>
I like starting out all my projects by imagining the finished product, so I sat down and drew it with pen and paper like a caveman,
Started out with the drawing system and used the heap 2D array style game again, Honestly I don't know what's my obsession with 2D arrays,
For the past 4 projects I've been spamming 2D arrays left right and center but to be fair they're incredibly effective. Back to the topic at hand,
I added input handling, It was actually my first time really using scan I expected it to be much more inconvenient, but it weirdly had everything i needed
im used to how C barely has any functionality but the more I use it the more I'm shocked at how usable and fun C really is (ignoring seg faults every 2 seconds),
I think by that time I added the main logic loop but not rly anything to do with the game not sure honestly feel free to fact-check me with the commit history

---

<h4> Day 2:</h4>

I spent the majority of day 2 trying to figure out how to flood fill, I tried many approaches and I mean many some of my favorites by far (Lazer fill, Segfault fill and last but not least floodfill)
Lazer fill was the first I tried I based it off of rook movement in chess and how they map the board with col and row if you increment it right,
This originally came to me because of my chess engine I made a while back feel free to check it out #shameless-promo, Anyway it didn't work out in the end for very good reasons I can't really properly explain them,
so I recommend trying to implement it yourself that's the only way and easiest way to get it, Onto the next approach: Segfault fill, I named it Segfault fill due to the fact that 
it segfaults when ran, The algorithm its self for this one is actually correct, and it fully worked, but I ran out of stack before it ever finished </3, And last but not the least flood filling which I've stuck to for now (or at least tried my best to implement).

---

<h4> Day 3:</h4>
Made the readme for the project and this devjournal also added score system and exit functionality, Added point system that tracks highest score and current score based on how many flags have been placed correctly, Added clean heap freeing so valgrind doesn't haunt my dreams again, 
Added different playing levels (Hard, Medium, Easy) with ranging size scaling and mine count for replayability, Made a play again option, Added persistent storage saving and decided to pivot from only minesweeper cli to "gamify" multiple games for your terminal not sure what game i wanna add just yet
