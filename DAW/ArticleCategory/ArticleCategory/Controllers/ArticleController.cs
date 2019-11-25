using ArticleCategory.Models;
using Microsoft.AspNet.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ArticleCategory.Controllers
{
    [Authorize]
    public class ArticleController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();
        // GET: Article
        [Authorize(Roles = "User,Editor,Administrator")]
        public ActionResult Index()
        {
            var articles = db.Articles.Include("Category").Include("User");

            ViewBag.Articles = articles;

            return View();
        }

        [HttpGet]
        [Authorize(Roles = "User,Editor,Administrator")]
        public ActionResult Show(int id)
        {
            Article article = db.Articles.Find(id);

            ViewBag.Article = article;
            ViewBag.Category = article.category;

            ViewBag.afisareButoane = false;
            if (User.IsInRole("Editor") || User.IsInRole("Administrator"))
            {
                ViewBag.afisareButoane = true;
            }

            ViewBag.esteAdmin = User.IsInRole("Administrator");
            ViewBag.UtilizatorCurent = User.Identity.GetUserId();

            return View(article);
        }

        [HttpGet]
        [Authorize(Roles = "Editor,Administrator")]
        public ActionResult New()
        {
            Article article = new Article();
            var categories = from cat in db.Categories select cat;
            ViewBag.Categories = categories;

            article.UserId = User.Identity.GetUserId();

            return View("GetNew", article);
        }

        [HttpPost]
        [Authorize(Roles = "Editor,Administrator")]
        public ActionResult New(Article article)
        {
            var categories = from cat in db.Categories select cat;
            ViewBag.Categories = categories;
            try
            {
                if (ModelState.IsValid)
                {
                    db.Articles.Add(article);
                    db.SaveChanges();
                    TempData["message"] = "Am adaugat un nou articol";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View("GetNew",article);
                }
            }
            catch (Exception e)
            {
                return View("NewErr");
            }

            
        }

        [HttpGet]
        [Authorize(Roles = "Editor,Administrator")]
        public ActionResult Edit(int id)
        {

            Article article = db.Articles.Find(id);
            article.UserId = User.Identity.GetUserId();
            
            ViewBag.Article = article; 
            ViewBag.Category = article.category; 
            
            var categories = from cat in db.Categories select cat; 
            
            ViewBag.Categories = categories;

            if (article.UserId == User.Identity.GetUserId() || User.IsInRole("Administrator"))
            {
                return View(article);
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa faceti modificari!";
                return RedirectToAction("Index");
            }
        }

        [HttpPut]
        [Authorize(Roles = "Editor, Administrator")]
        public ActionResult Edit(int id, Article requestArticle) 
        {
            try
            {
                var article = db.Articles.Find(id);

                /*if (TryUpdateModel(article)) 
                { 
                    article.Title = requestArticle.Title; 
                    article.Content = requestArticle.Content; 
                    article.Date = requestArticle.Date; 
                    article.CategoryId = requestArticle.CategoryId;
                    db.SaveChanges(); 

                }*/

                if (article.UserId == User.Identity.GetUserId() || User.IsInRole("Administrator"))
                {
                    if (ModelState.IsValid)
                    {
                        article.Title = requestArticle.Title;
                        article.Content = requestArticle.Content;
                        article.Date = requestArticle.Date;
                        article.CategoryId = requestArticle.CategoryId;

                        db.Entry(article).State = System.Data.Entity.EntityState.Modified;
                        db.SaveChanges();
                    }
                    else
                    {
                        ViewBag.Category = article.category;

                        var categories = from cat in db.Categories select cat;

                        ViewBag.Categories = categories;
                        return View(requestArticle);
                    }
                }
                else
                {
                    TempData["message"] = "Nu aveti dreptul sa faceti modificari!";
                    return RedirectToAction("Index");   
                }

                return RedirectToAction("Index"); 
            } catch (Exception e)
            {
                System.Console.WriteLine(e.Message);
                return View("EditErr"); 
            } 
        }

        [HttpDelete]
        [Authorize(Roles = "Editor, Administrator")]
        public ActionResult Delete (int id)
        {
            var article = db.Articles.Find(id);

            if (article.UserId == User.Identity.GetUserId() || User.IsInRole("Administrator"))
            {
                db.Articles.Remove(article);
                db.SaveChanges();
            }
            else
            {
                TempData["message"] = "Nu aveti dreptul sa stergeti articolul!";
                return RedirectToAction("Index");
            }

            return RedirectToRoute("/Article/Index");
        }

    }
}