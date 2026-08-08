export function startGeneratorOrchestrator(generatorFn) {
    const generator = generatorFn();

    let lastTime = performance.now();
    let virtualTime = 0;

    function loop(currentTime) {
        let delta = currentTime - lastTime;
        lastTime = currentTime;

        // Cap delta to prevent massive jumps if the user tabs away
        if (delta > 32) delta = 32;

        // Drain any remaining sleep time from the last frame
        if (virtualTime > 0) {
            virtualTime -= delta;
        }

        let isDone = false;

        // While the generator is not waiting on a Sleep, process the next instructions synchronously
        while (virtualTime <= 0) {
            const { value, done } = generator.next();

            if (done) {
                isDone = true;
                break;
            }

            // The value yielded by the generator is the requested Sleep duration (e.g., yield 500)
            if (typeof value === 'number') {
                virtualTime += value;
            }
            // In a full implementation, you could also catch promises here (e.g. yield playSoundAsync)
        }

        // (At this point in the RAF loop, you would blit the offscreen buffer to the main canvas)

        if (!isDone) {
            requestAnimationFrame(loop);
        } else {
            console.log("Animation Finished!");
        }
    }

    requestAnimationFrame(loop);
}
