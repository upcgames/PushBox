export function createInputRouter() {
  const destinations = new Map();
  let linked = false;
  return {
    register(id, send) { destinations.set(id, send); return () => destinations.delete(id); },
    setLinked(value) { linked = !!value; },
    send(id, key) {
      if (linked) for (const send of destinations.values()) send(key);
      else destinations.get(id)?.(key);
    },
  };
}
