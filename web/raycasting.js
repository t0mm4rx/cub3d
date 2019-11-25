const MAP_SIZE = 20;
const WALLS = 40;
const MINIMAP_SIZE = 200;
const RAYS = 300;
const FOV = 45;
const ROTATE_SPEED = 4;
const SPEED = .08;
const TEXTURE_SIZE = 64;

var minimap = null;
var map = null;
var position = null;
var rays = [];
var resolution = 0;
var heading = null;

var map_fn = null;

var image_texture = null;

function preload()
{
    image_texture = loadImage("../res/brick.jpg");
}

function setup()
{
    frameRate(50);
    angleMode(DEGREES);

    createCanvas(1000, 1000);
    minimap = createGraphics(MINIMAP_SIZE, MINIMAP_SIZE);
    resolution = width / RAYS;

    map_fn = map;
    map = new Array(MAP_SIZE).fill().map(() => new Array(MAP_SIZE).fill(0));
    for (let i = 0; i < MAP_SIZE; i++)
    {
        map[i][0] = 1;
        map[0][i] = 1;
        map[MAP_SIZE - 1][i] = 1;
        map[i][MAP_SIZE - 1] = 1;
    }
    for (let _ = 0; _ < WALLS; _++) map[floor(random(0, MAP_SIZE))][floor(random(0, MAP_SIZE))] = 1;

    heading = createVector(1, 0);
    for (let i = 0; i < RAYS; i++)
    {
        let ray = heading.copy();
        ray.rotate(-FOV / 2);
        ray.rotate(i * FOV / RAYS);
        ray.distance = MAP_SIZE;
        ray.texture = '';
        ray.offsetS = 0;
        ray.offsetN = 0;
        ray.offsetE = 0;
        ray.offsetO = 0;
        rays.push(ray);
    }
    position = createVector(MAP_SIZE / 2, MAP_SIZE / 2);
}

function draw()
{
    //console.log(heading.heading());
    background(0);
    handle_inputs();
    process_rays();
    fill(100, 100, 200);
    rect(0, 0, width, height / 2);
    fill(40, 200, 20);
    rect(0, height / 2, width, height / 2);
    draw_rays();
    draw_minimap();
    fill(255);
    text(round(frameRate()), 10, 20);
}

function draw_rays()
{
    noStroke();
    for (let i = 0; i < RAYS; i++)
    {
        let color = map_fn(rays[i].distance, 0, MAP_SIZE, 255, 0);
        //let h = map_fn(rays[i].distance/* * Math.cos(rays[i].heading() / 360 * (2 * PI))*/, 0, MAP_SIZE, height, 10);
        let h = (height) / rays[i].distance;
        /*fill(color);
        rect(i * resolution, height / 2 + h / 2, resolution, -h);*/
        image(image_texture, i * resolution, height / 2 + h / 2, resolution, -h);
    }
}

function draw_minimap()
{
    minimap.background(50);
    minimap.noStroke();
    minimap.fill(200);
    for (let x = 0; x < MAP_SIZE; x++)
    {
        for (let y = 0; y < MAP_SIZE; y++)
        {
            if (map[x][y] == 1)
            {
                minimap.rect(x * MINIMAP_SIZE / MAP_SIZE, y * MINIMAP_SIZE / MAP_SIZE, MINIMAP_SIZE / MAP_SIZE, MINIMAP_SIZE / MAP_SIZE);
                //console.log(x * MAP_SIZE / MINIMAP_SIZE, y * MAP_SIZE / MINIMAP_SIZE, MAP_SIZE / MINIMAP_SIZE, MAP_SIZE / MINIMAP_SIZE);
            }
        }
    }
    minimap.stroke(200, 25, 10);
    minimap.strokeWeight(1);
    let x = map_fn(position.x, 0, MAP_SIZE, 0, MINIMAP_SIZE);
    let y = map_fn(position.y, 0, MAP_SIZE, 0, MINIMAP_SIZE);
    for (let ray of rays)
    {
        minimap.line(x, y, x + ray.x * map_fn(ray.distance, 0, MAP_SIZE, 0, MINIMAP_SIZE), y + ray.y * map_fn(ray.distance, 0, MAP_SIZE, 0, MINIMAP_SIZE));
    }
    image(minimap, 0, height - MINIMAP_SIZE);
}

function rotate_rays(angle)
{
    for (let ray of rays)
        ray.rotate(angle);
    heading.rotate(angle);
}

function process_rays()
{
    for (let ray of rays)
    {
        let min = MAP_SIZE;
        let left = raycast_left(ray);
        let right = raycast_right(ray);
        let top = raycast_top(ray);
        let bottom = raycast_bottom(ray);
        if (left < min)
        {
            ray.distance = left;
            min = left;
            ray.texture = "O";
        }
        if (right < min)
        {
            ray.distance = right;
            min = right;
            ray.texture = "E";
        }
        if (top < min)
        {
            ray.distance = top;
            min = top;
            ray.texture = "N";
        }
        if (bottom < min)
        {
            ray.distance = bottom;
            min = bottom;
            ray.texture = "S";
        }

    }
}

function handle_inputs()
{
    if (keyIsDown(LEFT_ARROW))
        rotate_rays(-ROTATE_SPEED);
    if (keyIsDown(RIGHT_ARROW))
        rotate_rays(ROTATE_SPEED);
    if (keyIsDown(87) || keyIsDown(UP_ARROW))
        position.add(heading.copy().mult(SPEED));
    if (keyIsDown(83) || keyIsDown(DOWN_ARROW))
        position.add(heading.copy().mult(-SPEED));
    if (keyIsDown(65))
        position.add(heading.copy().rotate(-90).mult(SPEED));
    if (keyIsDown(68))
        position.add(heading.copy().rotate(90).mult(SPEED));
}

function raycast_left(ray)
{
  let theta = ray.heading();
  if (theta >= 90 || theta <= -90)
    return MAP_SIZE;
  let cx = position.x;
  let cy = position.y;
  while (map[floor(cx)][floor(cy)] == 0 && cx < MAP_SIZE && cy < MAP_SIZE)
  {
    let nx = floor(cx + 1) - cx;
    if (nx == 0)
      nx = 1;
    let ny = Math.tan(theta / 360 * (2 * Math.PI)) * nx;
    cx += nx;
    cy += ny;
  }
  ray.offsetO = cy % TEXTURE_SIZE;
  return position.dist(createVector(cx, cy));
}

function raycast_right(ray)
{
  let theta = ray.heading();
  if (!(theta >= 90 || theta <= -90))
    return MAP_SIZE;
  let cx = position.x;
  let cy = position.y;
  while (map[floor(cx - 1)][floor(cy)] == 0 && cx > 0 && cy > 0)
  {
    let nx = -(cx - floor(cx));
    if (nx == 0)
      nx = -1;
    let ny = Math.tan(theta / 360 * (2 * Math.PI)) * nx;
    cx += nx;
    cy += ny;
  }
  ray.offsetE = cy % TEXTURE_SIZE;
  return position.dist(createVector(cx, cy));
}

function raycast_top(ray)
{
  let theta = ray.heading();
  if (theta < 0)
    return MAP_SIZE;
  let cx = position.x;
  let cy = position.y;
  while (cx < MAP_SIZE && cy < MAP_SIZE  && cx > 0 && cy > 0 && map[floor(cx)][floor(cy)] == 0)
  {
    let ny = floor(cy + 1) - cy;
    if (ny == 0)
      ny = 1;
    let nx = Math.tan((90 - theta) / 360 * (2 * Math.PI)) * ny;
    cx += nx;
    cy += ny;
  }
  ray.offsetN = cx % TEXTURE_SIZE;
  return position.dist(createVector(cx, cy));
}

function raycast_bottom(ray)
{
  let theta = ray.heading();
  if (theta > 0)
    return MAP_SIZE;
  let cx = position.x;
  let cy = position.y;
  while (cx < MAP_SIZE && cy < MAP_SIZE  && cx > 0 && cy > 0 && map[floor(cx)][floor(cy - 1)] == 0)
  {
    let ny = -(cy - floor(cy));
    if (ny == 0)
      ny = -1;
    let nx = Math.tan((90 - theta) / 360 * (2 * Math.PI)) * ny;
    cx += nx;
    cy += ny;
  }
  ray.offsetS = cx % TEXTURE_SIZE;
  return position.dist(createVector(cx, cy));
}
