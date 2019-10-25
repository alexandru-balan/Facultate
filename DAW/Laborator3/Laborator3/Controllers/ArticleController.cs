using Laborator3.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;


namespace Laborator3.Controllers
{
    public class ArticleController : Controller
    {
        // GET: Article
        public ActionResult Index()
        {
            Article[] articles = GetArticles();

            ViewBag.Articles = articles;

            return View();
        }

        [HttpGet]
        public ActionResult Show(int? id)
        {
            Article[] articles = GetArticles();

            if (id.HasValue)
            {
                ViewBag.Article = articles[id.Value];
                return View();
            }

            return Redirect("/article/show/" + id.Value);
        }

        public ActionResult ShowError (int id)
        {
            ViewBag.id = id;

            return View();
        }

        [HttpGet]
        public ActionResult New ()
        {
            ViewBag.id = new Random(42).Next();
            ViewBag.content = "NewContent";
            ViewBag.title = "NewTitle";
            return View();
        }

        [HttpPost]
        public ActionResult New (int id, string title, string content)
        {
            Article article = new Article();
            article.Id = id;
            article.Title = title;
            article.Content = content;
            article.Date = DateTime.Now;

            ViewBag.Article = article;
            return View("NewPost");
        }

        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                ViewBag.id = id;
                return View();
            }
            else
                return View("EditError");
        }

        [HttpPut]
        public ActionResult Edit()
        {
            return View("EditPut");
        }

        
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                ViewBag.id = id.Value;
                return View();
            }

            else return View("DeleteError");
        }

        [HttpDelete]
        public ActionResult DeleteConf(int? id)
        {
            if (id.HasValue)
            {
                ViewBag.id = id.Value;
                return View("DeleteConfirm");
            }
            else
                return View("DeleteError");
        }

        [NonAction]
        public Article[] GetArticles ()
        {
            Article[] articles = new Article[3];

            for (int i = 0; i < 3; ++i)
            {
                Article article = new Article();
                article.Id = i;
                article.Title = "Articolul " + (i + 1).ToString();
                article.Content = "Continutul articolului " + (i + 1).ToString();
                article.Date = DateTime.Now;

                articles[i] = article;
            }

            return articles;
        }


    }
}