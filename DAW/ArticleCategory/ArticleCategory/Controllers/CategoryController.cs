using ArticleCategory.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace ArticleCategory.Controllers
{
    [Authorize(Roles = "Administrator")]
    public class CategoryController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();
        // GET: Category
        public ActionResult Index()
        {
            var Categories = from category in db.Categories
                             orderby category.CategoryId
                             select category;

            ViewBag.Categories = Categories;

            return View();
        }

        [HttpGet]
        public ActionResult Show (int id)
        {
            var category = db.Categories.Find(id);

            ViewBag.Category = category;
            ViewBag.Articles = category.Articles;

            return View(category);
        }

        [HttpGet]
        public ActionResult New ()
        {
            return View();
        }

        [HttpPost]
        public ActionResult New (Category category)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    db.Categories.Add(category);
                    db.SaveChanges();
                    TempData["message"] = "Categoria a fost adaugata";
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(category);
                }
            }
            catch (Exception ex)
            {
                return View();
            }
        }

        [HttpGet]
        public ActionResult Edit (int id)
        {
            var category = db.Categories.Find(id);

            ViewBag.Category = category;

            return View(category);
        }

        [HttpPut]
        public ActionResult Edit (int id, Category category)
        {
            try
            {
                var category1 = db.Categories.Find(id);

                if (ModelState.IsValid)
                {
                    if (TryUpdateModel(category1))
                    {
                        category1.CategoryName = category.CategoryName;
                        db.SaveChanges();
                    }
                    return RedirectToAction("Index");
                }
                else
                {
                    return View(category);
                }
            }
            catch (Exception e)
            {
                return View();
            }
        }

        [HttpDelete]
        public ActionResult Delete (int id)
        {
            Category category = db.Categories.Find(id);

            db.Categories.Remove(category);
            db.SaveChanges();

            return RedirectToAction("Index");
        }
    }
}