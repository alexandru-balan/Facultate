using Laborator4.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Laborator4.Controllers
{
    public class ArticleController : Controller
    {
        private ArticleDbContext db = new ArticleDbContext();
        private CategoryDbContext dbcat = new CategoryDbContext();
        // GET: Article
        public ActionResult Index()
        {
            var articles = db.Articles.Include("Category");

            ViewBag.Articles = articles;

            return View();
        }

        [HttpGet]
        public ActionResult Show(int id)
        {
            Article article = db.Articles.Find(id);

            ViewBag.Article = article;
            ViewBag.Category = article.category;

            return View();
        }

        [HttpGet]
        public ActionResult New()
        {
            var categories = from cat in dbcat.Categories select cat;
            ViewBag.Categories = categories;
            return View("GetNew");
        }

        [HttpPost]
        public ActionResult New(Article article)
        {
            try
            {
                db.Articles.Add(article);
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            catch (Exception e)
            {
                return View("NewErr");
            }

            
        }

        [HttpGet]
        public ActionResult Edit(int id)
        {

            Article article = db.Articles.Find(id); 
            
            ViewBag.Article = article; 
            ViewBag.Category = article.category; 
            
            var categories = from cat in dbcat.Categories select cat; 
            
            ViewBag.Categories = categories; 
            
            return View();
        }

        [HttpPut] public ActionResult Edit(int id, Article requestArticle) 
        { 
            try { 
                Article article = db.Articles.Find(id); 
                
                if (TryUpdateModel(article)) 
                { 
                    article.Title = requestArticle.Title; 
                    article.Content = requestArticle.Content; 
                    article.Date = requestArticle.Date; 
                    article.CategoryId = requestArticle.CategoryId; 
                    db.SaveChanges(); 
                } 
                return RedirectToAction("Index"); 
            } catch (Exception e) 
            { 
                return View("EditErr"); 
            } 
        }


    }
}